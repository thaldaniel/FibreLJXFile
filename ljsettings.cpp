#include "ljsettings.h"
#include <QString>
#include <QList>
#include <stdexcept>
#include <iostream>

bool LJSettings::isLJX(LJSensorType sensor)
{
    return (sensor == LJ_X8020 || sensor == LJ_X8080 || sensor == LJ_X8200 || sensor == LJ_X8400 || sensor == LJ_X8900);
}

bool LJSettings::isLJV(LJSensorType sensor)
{
    return (sensor == LJ_V7020 || sensor == LJ_V7060 || sensor == LJ_V7080 || sensor == LJ_V7200 || sensor == LJ_V7300 || sensor == LJ_V7020K || sensor == LJ_V7060K);
}

LJSettings::LJSettings()
{
    m_enviroment_settings.ip_address[0] = 192;
    m_enviroment_settings.ip_address[1] = 168;
    m_enviroment_settings.ip_address[2] = 0;
    m_enviroment_settings.ip_address[3] = 1;
    m_enviroment_settings.tcp_command_port = 24691;
    m_enviroment_settings.tcp_highspeed_port = 24692;
}

QByteArray LJSettings::getData()
{
    FibreLJXSettings s;
    s.sensor = m_sensor;
    s.enviroment = m_enviroment_settings;
    s.common = m_common;
    s.active_program = m_active_program;
    for(int i = 0; i < 16; i++) {
        s.programs[i] = m_programms[i];
        s.sensorSN[i] = m_sensor_sn[i];
        s.controllerSN[i] = m_controller_sn[i];
    }

    return QByteArray((char*)&s, sizeof(FibreLJXSettings));
}

void LJSettings::setData(QByteArray &data)
{
    FibreLJXSettings *s = (FibreLJXSettings *) (data.constData());
    m_sensor = s->sensor;
    m_enviroment_settings = s->enviroment;
    m_common = s->common;
    m_active_program = s->active_program;
    for(int i = 0; i < 16; i++) {
        m_programms[i] = s->programs[i];
        m_sensor_sn[i] = s->sensorSN[i];
        m_controller_sn[i] = s->controllerSN[i];
    }
}

// @param program: Program number 0-15
LJX8IF_TARGET_SETTING LJSettings::getTargetSetting(Parameter param, unsigned char program)
{
    program = (program & 0x0F) | 0x10;
    switch(param) {
    case DeviceName:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x00);
    case OperationAtNextPowerOn:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x01);
    case HighSpeedCommunicationBandRestriction:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x02);
    case MTUDuringHighSpeedCommunication:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x03);
    case IPAddress:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x04);
    case SubnetMask:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x05);
    case Gateway:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x06);
    case TCPCommandPortNumber:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x07);
    case TCPHighSpeedPortNumber:
        return LJX8IF_TARGET_SETTING(0x01, 0x00, 0x08);
    case MemoryAllocation:
        return LJX8IF_TARGET_SETTING(0x02, 0x00, 0x01);
    case OperationWhenMemoryFull:
        return LJX8IF_TARGET_SETTING(0x02, 0x00, 0x02);
    case ParallelImaging:
        return LJX8IF_TARGET_SETTING(0x02, 0x00, 0x03);
    case TRGMinimumInputTime:
        return LJX8IF_TARGET_SETTING(0x02, 0x00, 0x06);
    case ENCODERMinimumInputTime:
        return LJX8IF_TARGET_SETTING(0x02, 0x00, 0x07);
    case ControlTerminalMinimumInputTime:
        return LJX8IF_TARGET_SETTING(0x02, 0x00, 0x08);
    case BrightnessOutput:
        return LJX8IF_TARGET_SETTING(0x02, 0x00, 0x0B);
    case TriggerMode:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x01);
    case SamplingCycle:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x02);
    case BatchMeasurement:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x03);
    case InterTriggerPitch:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x04);
    case InterTriggerPitchCount:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x05);
    case MutualInterferencePrevention:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x06);
    case InputMode:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x07);
    case SubSampling:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x08);
    case PointsToSubSample:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x09);
    case BatchCount:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x0A);
    case SynchronizatonOfMultipleControllers:
        return LJX8IF_TARGET_SETTING(program, 0x00, 0x0B);
    case Binning:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x01);
    case MeasurementRangeXDirection:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x02);
    case MeasurementRangeZDirection:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x03);
    case DynamicRange:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x05);
    case ExposureTime:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x06);
    case ExposureMode:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x07);
    case MultiEmissionDetailsOptimizedLightIntensity:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x08);
    case MultiEmissionDetailsSynthesis:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x09);
    case InvalidDataInterpolationCount:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x10);
    case PeakSelection:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x11);
    case PeakWidthFilter:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x12);
    case StrayLightSuppressionFunction:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x14);
    case MaskSetting:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x0A);
    case LightIntensityControlMode:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x0B);
    case LightIntensityControlLowerLimitValue:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x0C);
    case LightIntensityControlUpperLimitValue:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x0D);
    case LightIntensityControlTargetArea:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x0E);
    case PeakDetectionSensitivity:
        return LJX8IF_TARGET_SETTING(program, 0x01, 0x0F);
    case SubSamplingXAxis:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x02);
    case DeadZoneDataInterpolation:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x05);
    case ReverseX:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x06);
    case ReverseZ:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x07);
    case ShiftX:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x08);
    case ShiftZ:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x09);
    case HeightCorection:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x10);
    case MedianXAxis:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x0A);
    case Smoothing:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x0B);
    case MedianZAxis:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x0C);
    case Averaging:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x0D);
    case InvalidDataProcessingz:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x0E);
    case TiltCorrection:
        return LJX8IF_TARGET_SETTING(program, 0x02, 0x0F);
    default:
        return LJX8IF_TARGET_SETTING();
    }
}

void LJSettings::setSettingRaw(LJX8IF_TARGET_SETTING target, char* data, int length)
{
    switch(target.byType) {
    case(0x01): //Environment Settings
        switch(target.byItem) {
        case 0x00: //DeviceName:
            for(int i = 0; i < 32; i++) {
                m_enviroment_settings.device_name[i] = data[i];
            }
            break;
        case 0x01://OperationAtNextPowerOn:
            m_enviroment_settings.operation_at_next_power_on = data[0];
            break;
        case 0x02://HighSpeedCommunicationBandRestriction:
            m_enviroment_settings.high_speed_communication_band_restriction = data[0];
            break;
        case 0x03://MTUDuringHighSpeedCommunication:
            m_enviroment_settings.mtu_during_high_speed_communication = ((data[1] &0xFF) << 8 | (data[0] & 0xFF));
            break;
        case 0x04://IPAddress:
            for(int i = 0; i < 4; i++) {
                m_enviroment_settings.ip_address[i] = data[i];
            }
            break;
        case 0x05://SubnetMask:
            for(int i = 0; i < 4; i++) {
                m_enviroment_settings.subnet_mask[i] = data[i];
            }
            break;
        case 0x06://Gateway:
            for(int i = 0; i < 4; i++) {
                m_enviroment_settings.gateway[i] = data[i];
            }
            break;
        case 0x07://TCPCommandPortNumber:
            m_enviroment_settings.tcp_command_port = ((data[1] &0xFF) << 8 | (data[0] & 0xFF));
            break;
        case 0x08://TCPHighSpeedPortNumber:
            m_enviroment_settings.tcp_highspeed_port = ((data[1] &0xFF) << 8 | (data[0] & 0xFF));
            break;
        }
        break;
    case(0x02): //Common Settings
        switch(target.byItem) {
        case(0x01)://MemoryAllocation,
            m_common.memory_allocation = data[0];
            break;
        case(0x02)://        OperationWhenMemoryFull,
            m_common.operation_when_memory_full = data[0];
            break;
        case(0x03)://        ParallelImaging,
            m_common.parallel_imaging = data[0];
            break;
        case(0x06)://        TRGMinimumInputTime,
            m_common.trg_minimum_input_time = data[0];
            break;
        case(0x07)://        ENCODERMinimumInputTime,
            m_common.encoder_minimum_input_time = data[0];
            break;
        case(0x08)://        ControlTerminalMinimumInputTime,
            m_common.control_terminal_minimum_input_time = data[0];
            break;
        case(0x0B): //        BrightnessOutput,
            m_common.brightness_output = data[0];
            break;
        }
        break;
    default:
        if(target.byType >= 0x10 && target.byType <= 0x1F) {
            switch(target.byCategory) {
            case(0x00):
                switch(target.byItem) {
                case(0x01):
                    m_programms[target.byType & 0x0F].triggerMode = data[0];
                    break;
                case(0x02):
                    m_programms[target.byType & 0x0F].samplingCycle = data[0];
                    break;
                case(0x03):
                    m_programms[target.byType & 0x0F].batchMeasurement = data[0];
                    break;
                case(0x0A):
                    m_programms[target.byType & 0x0F].batchCount = ((data[1] &0xFF) << 8 | (data[0] & 0xFF));
                    break;
                case(0x04):
                    m_programms[target.byType & 0x0F].interTriggerPitch = data[0];
                    break;
                case(0x05):
                    m_programms[target.byType & 0x0F].interTriggerPitchCount = ((data[3] &0xFF) << 24 | (data[2] &0xFF) << 16 | (data[1] &0xFF) << 8 | (data[0] & 0xFF));
                    break;
                case(0x0B):
                    m_programms[target.byType & 0x0F].synchronization = data[0];
                    break;
                case(0x06):
                    m_programms[target.byType & 0x0F].mutualInterferencePrevention = data[0];
                    m_programms[target.byType & 0x0F].mutualInterferencePreventionSlaveEmission = data[1];
                    break;
                case(0x07):
                    m_programms[target.byType & 0x0F].encoderInputMode = data[0];
                    break;
                case(0x08):
                    m_programms[target.byType & 0x0F].subSamplingOptions = data[0];
                    break;
                case(0x09):
                    m_programms[target.byType & 0x0F].pointsToSubSample = ((data[1] &0xFF) << 8 | (data[0] & 0xFF));
                    break;
                default:
                    std::cerr << "Item not found at: LJSettings::setSettingRaw #1" << std::endl;
                }
                break;
            case(0x01):
                switch(target.byItem) {
                case(0x01):
                    m_programms[target.byType & 0x0F].binning = data[0];
                    break;
                case(0x02):
                    m_programms[target.byType & 0x0F].measurementRangeXDirection = data[0];
                    m_programms[target.byType & 0x0F].measurementRangeXDirectionCenter = ((data[3] &0xFF) << 8 | (data[2] & 0xFF));
                    break;
                case(0x03):
                    m_programms[target.byType & 0x0F].measurementRangeZDirection = data[0];
                    m_programms[target.byType & 0x0F].measurementRangeZDirectionCenter = ((data[3] &0xFF) << 8 | (data[2] & 0xFF));
                    m_programms[target.byType & 0x0F].measurementRangeZDirectionBinning = data[5];
                    break;
                case(0x05):
                    m_programms[target.byType & 0x0F].dynamicRange = data[0];
                    break;
                case(0x06):
                    m_programms[target.byType & 0x0F].exposureTime = data[0];
                    break;
                case(0x07):
                    m_programms[target.byType & 0x0F].exposureMode = data[0];
                    break;
                case(0x08):
                    m_programms[target.byType & 0x0F].multiEmissionDetailsOptimizedLightIntensity = data[0];
                    break;
                case(0x09):
                    m_programms[target.byType & 0x0F].multiEmissionSynthesis = data[0];
                    break;
                case(0x0A):
                    //#TODO Target1 Selection in Mask Setting
                    std::cout << "ToDo 4 mask here" << std::endl;
                    break;
                case(0x0B):
                    m_programms[target.byType & 0x0F].lightIntensityControlMode = data[0];
                    break;
                case(0x0C):
                    m_programms[target.byType & 0x0F].lightIntensityUpperLimit = data[0];
                    break;
                case(0x0D):
                    m_programms[target.byType & 0x0F].lightIntensityLowerLimit = data[0];
                    break;
                case(0x0E):
                    m_programms[target.byType & 0x0F].lightIntensityControlTargetAreaStart = ((data[1] &0xFF) << 8 | (data[0] & 0xFF));
                    m_programms[target.byType & 0x0F].lightIntensityControlTargetAreaStop = ((data[3] &0xFF) << 8 | (data[2] & 0xFF));
                    break;
                case(0x0F):
                    m_programms[target.byType & 0x0F].peakDetectionSensitivity = data[0];
                    break;
                case(0x10):
                    m_programms[target.byType & 0x0F].invalidDataInterpolationCount = data[0];
                    break;
                case(0x11):
                    m_programms[target.byType & 0x0F].peakSelection = data[0];
                    break;
                case(0x12):
                    m_programms[target.byType & 0x0F].peakWidthFilter = data[0];
                    m_programms[target.byType & 0x0F].peakWidthFilterStrength = data[1];
                    break;
                case(0x14):
                    m_programms[target.byType & 0x0F].strayLightSuppressionFunction = data[0];
                    m_programms[target.byType & 0x0F].strayLightSuppressionFunctionFilterStrength = data[1];
                    break;
                default:
                    std::cerr << "Item not found at: LJSettings::setSettingRaw #2" << std::endl;
                    break;
                }
                break;
            case(0x02):
                switch(target.byItem) {
                case(0x02):
                    m_programms[target.byType & 0x0F].subSamplingXAxis = data[0];
                    break;
                case(0x05):
                    m_programms[target.byType & 0x0F].deadZoneDataInterpolation = data[0];
                    break;
                case(0x06):
                    m_programms[target.byType & 0x0F].reverseX = data[0];
                    break;
                case(0x07):
                    m_programms[target.byType & 0x0F].reverseZ = data[0];
                    break;
                case(0x08):
                    m_programms[target.byType & 0x0F].shiftX = data[0];
                    break;
                case(0x09):
                    m_programms[target.byType & 0x0F].shiftZ = data[0];
                    break;
                case(0x0A):
                    m_programms[target.byType & 0x0F].medianXAxis = data[0];
                    break;
                case(0x0C):
                    m_programms[target.byType & 0x0F].medianYAxis = data[0];
                    break;
                case(0x0B):
                    m_programms[target.byType & 0x0F].smoothing = data[0];
                    break;
                case(0x0D):
                    m_programms[target.byType & 0x0F].averagingCount = data[0];
                    break;
                case(0x0E):
                    m_programms[target.byType & 0x0F].invalidDataProcessingYProcessCount = data[0];
                    m_programms[target.byType & 0x0F].invalidDataProcessingYResumeCount = data[1];
                    break;
                case(0x0F):
                    m_programms[target.byType & 0x0F].tiltCorrectionOnOff = data[0];
                    m_programms[target.byType & 0x0F].tiltCorrectionLineCalculationAreaCount = data[4];
                    m_programms[target.byType & 0x0F].tiltCorrectionAreaStartPosition1 = ((data[11] &0xFF) << 24 | (data[10] &0xFF) << 16 | (data[9] &0xFF) << 8 | (data[8] & 0xFF));
                    m_programms[target.byType & 0x0F].tiltCorrectionAreaEndPosition1 = ((data[15] &0xFF) << 24 | (data[14] &0xFF) << 16 | (data[13] &0xFF) << 8 | (data[12] & 0xFF));
                    m_programms[target.byType & 0x0F].tiltCorrectionAreaStartPosition2 = ((data[19] &0xFF) << 24 | (data[18] &0xFF) << 16 | (data[17] &0xFF) << 8 | (data[16] & 0xFF));
                    m_programms[target.byType & 0x0F].tiltCorrectionAreaEndPosition2 = ((data[23] &0xFF) << 24 | (data[22] &0xFF) << 16 | (data[21] &0xFF) << 8 | (data[20] & 0xFF));
                    m_programms[target.byType & 0x0F].tiltCorrectionPostCorrectionAngle = ((data[25] &0xFF) << 8 | (data[24] & 0xFF));
                    m_programms[target.byType & 0x0F].tiltCorrectionCorrectionAngle = ((data[27] &0xFF) << 8 | (data[26] & 0xFF));
                    break;
                case(0x10):
                    m_programms[target.byType & 0x0F].heightCorrectionOnOff = data[0];
                    m_programms[target.byType & 0x0F].heightCorrectionAreaStartPosition1 = ((data[7] &0xFF) << 24 | (data[6] &0xFF) << 16 | (data[5] &0xFF) << 8 | (data[4] & 0xFF));
                    m_programms[target.byType & 0x0F].heightCorrectionAreaEndPosition1 = ((data[11] &0xFF) << 24 | (data[10] &0xFF) << 16 | (data[9] &0xFF) << 8 | (data[8] & 0xFF));
                    m_programms[target.byType & 0x0F].heightCorrectionAreaStartPosition2 = ((data[15] &0xFF) << 24 | (data[14] &0xFF) << 16 | (data[13] &0xFF) << 8 | (data[12] & 0xFF));
                    m_programms[target.byType & 0x0F].heightCorrectionAreaEndPosition2 = ((data[19] &0xFF) << 24 | (data[18] &0xFF) << 16 | (data[17] &0xFF) << 8 | (data[16] & 0xFF));
                    m_programms[target.byType & 0x0F].heightCorrectionPostCorrectionHeight = ((data[23] &0xFF) << 24 | (data[22] &0xFF) << 16 | (data[21] &0xFF) << 8 | (data[20] & 0xFF));
                    m_programms[target.byType & 0x0F].heightCorrectionSpan = ((data[27] &0xFF) << 24 | (data[26] &0xFF) << 16 | (data[25] &0xFF) << 8 | (data[24] & 0xFF));
                    break;
                default:
                    std::cerr << "Item not found at: LJSettings::setSettingRaw #3" << std::endl;
                }
                break;
            default:
                std::cerr << "Category not found at: LJSettings::setSettingRaw #1" << std::endl;
            }


        } else {
            std::cerr << "target not found in LJSettings::setSettingRaw" << std::endl;
        }
    }
}

void LJSettings::print()
{
    std::cout << "Sensor SN: " << sensorSN() << std::endl;
    std::cout << "Controller SN: " << controllerSN() << std::endl;
    std::cout << "----- Environment Settings -----" << std::endl;
    std::cout << "DeviceName: \t\t\t" << deviceName() << std::endl;
    std::cout << "OperationAtNextPowerOn: \t\t" << operationAtNextPowerOnString() << std::endl;
    std::cout << "HighSpeedCommunicationBandRestriction: \t" << highSpeedCommunicationBandRestrictionString() << std::endl;
    std::cout << "MTU during high-speed communication: \t" << mtuDuringHighSpeedCommunicaton() << std::endl;
    std::cout << "IP-Adress: \t\t\t" << ipAddress() << std::endl;
    std::cout << "Subnet: \t\t\t\t" << subnetMask() << std::endl;
    std::cout << "Gateway: \t\t\t\t" << gateway() << std::endl;
    std::cout << "TCP Command Port: \t\t\t" << tcpCommandPort() << std::endl;
    std::cout << "TCP Highspeed Port: \t\t" << tcpHighspeedPort() << std::endl;

    std::cout << "----- Common Settings -----" << std::endl;
    std::cout << "MemoryAllocation: \t\t\t" << memoryAllocationString() << std::endl;
    std::cout << "OperationWhenMemoryFull: \t\t" << operationWhenMemoryFullString() << std::endl;
    std::cout << "ParallelImaging: \t\t\t" << parallelImagingString() << std::endl;
    std::cout << "TRGMinimumInputTime: \t\t" << trgMinimumInputTimeString() << std::endl;
    std::cout << "ENCODERMinimumInputTime: \t\t" << encoderMinimumInputTimeString() << std::endl;
    std::cout << "ControlTerminalMinimumInputTime:\t" << controlTerminalMinimumInputTimeString() << std::endl;
    std::cout << "BrightnessOutput: \t\t\t" << brightnessOutputString() << std::endl;

    printProgram();
}

void LJSettings::printProgram(int program)
{
    bool active = program == -1 ? true : false;
    if(active)
        program = (int)activeProgram();
    std::cout << "----- Programm Settings No. " << program;
    if(active)
        std::cout << "(Active)";
    std::cout << " -----" << std::endl;
    std::cout << "Trigger mode: \t\t\t\t" << triggerModeString(program) << std::endl;
    std::cout << "SamplingCycle: \t\t\t\t" << samplingCycleString(program) << std::endl;
    std::cout << "BatchMeasurement: \t\t\t\t" << batchMeasurementString(program) << std::endl;
    std::cout << "BatchCount: \t\t\t\t" << batchCount(program) << std::endl;
    std::cout << "InterTriggerPitch: \t\t\t\t" << interTriggerPitchString(program) << std::endl;
    std::cout << "InterTriggerPitchCount: \t\t\t" << interTriggerPitchCountString(program) << std::endl;
    std::cout << "SynchronizatonOfMultipleControllers: \t\t" << synchronizationString(program) << std::endl;
    std::cout << "MutualInterferencePrevention: \t\t" << mutualInterferencePreventionString(program) << std::endl;
    std::cout << "MutualInterferencePreventionSlaveEmission: \t" << mutualInterferencePreventionSlaveEmissionString(program) << std::endl;
    std::cout << "InputMode: \t\t\t\t" << encoderInputModeString(program) << std::endl;
    std::cout << "SubSampling: \t\t\t\t" << subSamplingOptionsString(program) << std::endl;
    std::cout << "PointsToSubSample: \t\t\t\t" << pointsToSubSample(program) << std::endl;
    std::cout << std::endl;
    std::cout << "Binning: \t\t\t\t" << binningString(program) << std::endl;
    std::cout << "MeasurementRangeXDirection: \t\t" << measurementRangeXDirectionString(program) << std::endl;
    std::cout << "Center X of the measurement range: \t" << measurementRangeXDirectionCenter(program) << std::endl;
    std::cout << "MeasurementRangeZDirection: \t\t" << measurementRangeZDirectionString(program) << std::endl;
    std::cout << "Center Z of the measurement range: \t" << measurementRangeZDirectionCenter(program) << std::endl;
    std::cout << "Binning (Z) \t\t\t" << measurementRangeZDirectionBinningString(program) << "\t(Only valid on the LJ-x8080 head)" << std::endl;
    std::cout << "DynamicRange: \t\t\t" << dynamicRangeString(program) << std::endl;
    std::cout << std::endl;
    std::cout << "ExposureTime: \t\t\t\t" << exposureTimeString(program) << std::endl;
    std::cout << "ExposureMode: \t\t\t\t" << exposureModeString(program) << std::endl;
    std::cout << "MultiEmissionDetailsOptimizedLightIntensity: \t" << multiEmissionDetailsOptimizedLightIntensityString(program) << std::endl;
    std::cout << "MultiEmissionDetailsSynthesis: \t\t" << multiEmissionSynthesisString(program) << std::endl;
    std::cout << "MaskSetting: \t\t" << "TODO " << (program) << std::endl;

    std::cout << "LightIntensityControlMode: \t\t" << lightIntensityControlModeString(program) << std::endl;
    std::cout << "LightIntensityControlLowerLimitValue: \t" << (int)lightIntensityLowerLimit(program) << std::endl;
    std::cout << "LightIntensityControlUpperLimitValue: \t" << (int)lightIntensityUpperLimit(program) << std::endl;
    std::cout << "LightIntensityControlTargetArea Start: \t" << lightIntensityControlTargetAreaStartString(program) << std::endl;
    std::cout << "LightIntensityControlTargetArea Stop: \t" << lightIntensityControlTargetAreaStopString(program) << std::endl;
    std::cout << "PeakDetectionSensitivity: \t\t" << (int)peakDetectionSensitivity(program) << std::endl;
    std::cout << "InvalidDataInterpolationCount: \t" << (int)invalidDataInterpolationCount(program) << std::endl;
    std::cout << "PeakSelection: \t\t\t" << peakSelectionString(program) << std::endl;

    std::cout << "PeakWidthFilter: \t\t\t\t" << peakWidthFilterString(program) << std::endl;
    std::cout << "PeakWidthFilter Strength: \t\t\t" << (int)peakWidthFilterStrength(program) << std::endl;
    std::cout << "StrayLightSuppressionFunction: \t\t" << strayLightSuppressionFunctionString(program) << "\t(Disabled with LJ-V head)" << std::endl;
    std::cout << "StrayLightSuppressionFunction Filter Strength: \t" << (int)strayLightSuppressionFunctionFilterStrength() << "\t1 (weak) to 3 (strong) \t (Disabled with LJ-V head)" << std::endl;
    std::cout << "SubSamplingXAxis: \t\t\t\t" << subSamplingXAxisString(program) << std::endl;
    std::cout << "DeadZoneDataInterpolation: \t\t\t" << deadZoneDataInterpolationString(program) << std::endl;
    std::cout << "ReverseX: \t\t\t\t" << reverseXString(program) << std::endl;
    std::cout << "ReverseZ: \t\t\t\t" << reverseZString(program) << std::endl;
    std::cout << "ShiftX: \t\t\t\t\t" << shiftX(program) << std::endl;
    std::cout << "ShiftZ: \t\t\t\t\t" << shiftZ(program) << std::endl;

    std::cout << "MedianXAxis: \t\t\t" << medianXAxisString(program) << std::endl;
    std::cout << "MedianZAxis: \t\t\t" << medianYAxisString(program) << std::endl;
    std::cout << "Smoothing: \t\t\t" << smoothingString(program) << std::endl;
    std::cout << "Averaging: \t\t\t" << averagingCountString(program) << std::endl;
    std::cout << "InvalidDataProcessing Process count: \t" << (int)invalidDataProcessingYProcessCount(program) << std::endl;
    std::cout << "InvalidDataProcessing Resume count: \t" << (int)invalidDataProcessingYResumeCount(program) << std::endl;
    std::cout << "TiltCorrection: \t\t\t" << tiltCorrectionOnOffString(program) << std::endl;
    std::cout << "tiltCorrectionLineCalculationAreaCount:\t" << tiltCorrectionLineCalculationAreaCountString(program) << std::endl;
    std::cout << "tiltCorrectionAreaStartPosition1: \t" << tiltCorrectionAreaStartPosition1(program) << std::endl;
    std::cout << "tiltCorrectionAreaEndPosition1: \t" << tiltCorrectionAreaEndPosition1(program) << std::endl;
    std::cout << "tiltCorrectionAreaStartPosition2: \t" << tiltCorrectionAreaStartPosition2(program) << std::endl;
    std::cout << "tiltCorrectionAreaEndPosition2: \t" << tiltCorrectionAreaEndPosition2(program) << std::endl;
    std::cout << "tiltCorrectionPostCorrectionAngle: \t" << tiltCorrectionPostCorrectionAngle(program) << std::endl;
    std::cout << "tiltCorrectionAngle: \t\t" << tiltCorrectionCorrectionAngle(program) << std::endl;
    std::cout << "HeightCorection: \t\t" << ((heightCorrectionOnOff(program) == HeightCorrection_OFF) ? "OFF" : "ON") << std::endl;
}

LJSensorType LJSettings::sensor()
{
    return m_sensor;
}

LJX8IF_ETHERNET_CONFIG LJSettings::ethernetConfig()
{
    LJX8IF_ETHERNET_CONFIG c;
    c.abyIpAddress[0] = m_enviroment_settings.ip_address[0];
    c.abyIpAddress[1] = m_enviroment_settings.ip_address[1];
    c.abyIpAddress[2] = m_enviroment_settings.ip_address[2];
    c.abyIpAddress[3] = m_enviroment_settings.ip_address[3];
    c.wPortNo = m_enviroment_settings.tcp_command_port;
    return c;
}

std::string LJSettings::deviceName()
{
    return std::string(m_enviroment_settings.device_name);
}

void LJSettings::setDeviceName(std::string name)
{
    for(int i = 0; i < 32; i++) {
        if(i < name.length())
            m_enviroment_settings.device_name[i] = name.at(i);
        else
            m_enviroment_settings.device_name[i] = ' ';
    }
}

OperationAtNextPowerOnOptions LJSettings::operationAtNextPowerOn()
{
    return (OperationAtNextPowerOnOptions) m_enviroment_settings.operation_at_next_power_on;
}

std::string LJSettings::operationAtNextPowerOnString()
{
    switch(m_enviroment_settings.operation_at_next_power_on) {
    case (OperationAtNextPowerOn_BOOTP):
        return "BOOTP";
    case OperationAtNextPowerOn_BOOTPThenIPAddressFixed:
        return "BOOTPThenIPAddressFixed";
    case OperationAtNextPowerOn_IPAddressFixed:
        return "IPAddressFixed";
    default:
        return std::to_string(m_enviroment_settings.operation_at_next_power_on);
    }
}

void LJSettings::setOperationAtNextPowerOn(OperationAtNextPowerOnOptions option)
{
    m_enviroment_settings.operation_at_next_power_on = option;
}

HighSpeedCommunicationBandRestrictionOptions LJSettings::highSpeedCommunicationBandRestriction()
{
    return (HighSpeedCommunicationBandRestrictionOptions) m_enviroment_settings.high_speed_communication_band_restriction;
}

std::string LJSettings::highSpeedCommunicationBandRestrictionString()
{
    switch (m_enviroment_settings.high_speed_communication_band_restriction) {
    case HighSpeedCommunicationBandRestriction_OFF:
        return "OFF";
    case HighSpeedCommunicationBandRestriction_100Mbps:
        return "100Mbps";
    case HighSpeedCommunicationBandRestriction_200Mbps:
        return "200Mbps";
    case HighSpeedCommunicationBandRestriction_500Mbps:
        return "500Mbps";
    default:
        return std::to_string((int)m_enviroment_settings.high_speed_communication_band_restriction);
    }
}

void LJSettings::setHighSpeedCommunicationBandRestricton(HighSpeedCommunicationBandRestrictionOptions option)
{
    m_enviroment_settings.high_speed_communication_band_restriction = option;
}

unsigned short LJSettings::mtuDuringHighSpeedCommunicaton()
{
    return m_enviroment_settings.mtu_during_high_speed_communication;
}

void LJSettings::setMtuDuringHighSpeedCommunication(unsigned short option)
{
    m_enviroment_settings.mtu_during_high_speed_communication = option;
}

std::string LJSettings::ipAddress()
{
    std::string s;
    s += std::to_string(m_enviroment_settings.ip_address[0]);
    s += ".";
    s += std::to_string(m_enviroment_settings.ip_address[1]);
    s += ".";
    s += std::to_string(m_enviroment_settings.ip_address[2]);
    s += ".";
    s += std::to_string(m_enviroment_settings.ip_address[3]);
    return s;
}

void LJSettings::setIpAddress(std::string ip)
{
    QList ip_parts =  QString::fromStdString(ip).split('.');
    if(ip_parts.length() != 4)
        throw std::invalid_argument("Die IP-Adresse ist ungültig");
    int part[4];
    part[0] = ip_parts[0].toInt();
    part[1] = ip_parts[1].toInt();
    part[2] = ip_parts[2].toInt();
    part[3] = ip_parts[3].toInt();
    if(part[0] < 0 || part[0] > 255 || part[1] < 0 || part[1] > 255 || part[2] < 0 || part[2] > 255 || part[3] < 0 || part[3] > 255 )
        throw std::invalid_argument("Die IP-Adresse ist ungültig");
    if(part[0] == 0 && part[1] == 0 && part[2] == 0 && part[3] == 0)
        throw std::invalid_argument("Die IP-Adresse 0.0.0.0 ist nicht zulässig");
    if(part[0] >= 224)
        throw std::invalid_argument("Der IP-Adressbereich 224.0.0.0-255.255.255.255 ist nicht zulässig");
    m_enviroment_settings.ip_address[0] = (unsigned char) part[0];
    m_enviroment_settings.ip_address[1] = (unsigned char) part[1];
    m_enviroment_settings.ip_address[2] = (unsigned char) part[2];
    m_enviroment_settings.ip_address[3] = (unsigned char) part[3];
}

std::string LJSettings::subnetMask()
{
    std::string s;
    s += std::to_string(m_enviroment_settings.subnet_mask[0]);
    s += ".";
    s += std::to_string(m_enviroment_settings.subnet_mask[1]);
    s += ".";
    s += std::to_string(m_enviroment_settings.subnet_mask[2]);
    s += ".";
    s += std::to_string(m_enviroment_settings.subnet_mask[3]);
    return s;
}

void LJSettings::setSubnetMask(std::string &mask)
{
    QList parts =  QString::fromStdString(mask).split('.');
    unsigned int m = 0;
    m |= (parts[0].toUInt() & 0x0000000F);
    m = m << 8;
    m |= (parts[1].toUInt() & 0x0000000F);
    m = m << 8;
    m |= (parts[2].toUInt() & 0x0000000F);
    m = m << 8;
    m |= (parts[3].toUInt() & 0x0000000F);
    m = m << 8;
    unsigned int x = 0xFFFFFFFF;
    bool v = false;
    for(int i = 0; i < 32; i++) {
        if( m == x)
            v = true;
        x = x << 1;
    }
    if(!v)
        throw std::invalid_argument("Die Subnetzmaske ist ungültig");
    m_enviroment_settings.subnet_mask[0] = (unsigned char) (m & 0x000000FF);
    m_enviroment_settings.subnet_mask[1] = (unsigned char) ((m >> 8) & 0x000000FF);
    m_enviroment_settings.subnet_mask[2] = (unsigned char) ((m >> 16) & 0x000000FF);
    m_enviroment_settings.subnet_mask[3] = (unsigned char) ((m >> 24) & 0x000000FF);
}

std::string LJSettings::gateway()
{
    std::string s;
    s += std::to_string(m_enviroment_settings.gateway[0]);
    s += ".";
    s += std::to_string(m_enviroment_settings.gateway[1]);
    s += ".";
    s += std::to_string(m_enviroment_settings.gateway[2]);
    s += ".";
    s += std::to_string(m_enviroment_settings.gateway[3]);
    return s;
}

void LJSettings::setGateway(std::string &gateway)
{
    QList ip_parts =  QString::fromStdString(gateway).split('.');
    if(ip_parts.length() != 4)
        throw std::invalid_argument("Die IP-Adresse ist ungültig");
    int part[4];
    part[0] = ip_parts[0].toInt();
    part[1] = ip_parts[1].toInt();
    part[2] = ip_parts[2].toInt();
    part[3] = ip_parts[3].toInt();
    if(part[0] < 0 || part[0] > 255 || part[1] < 0 || part[1] > 255 || part[2] < 0 || part[2] > 255 || part[3] < 0 || part[3] > 255 )
        throw std::invalid_argument("Die IP-Adresse ist ungültig");
    if(part[0] == 0 && part[1] == 0 && part[2] == 0 && part[3] == 0)
        throw std::invalid_argument("Die IP-Adresse 0.0.0.0 ist nicht zulässig");
    if(part[0] >= 224)
        throw std::invalid_argument("Der IP-Adressbereich 224.0.0.0-255.255.255.255 ist nicht zulässig");
    m_enviroment_settings.gateway[0] = (unsigned char) part[0];
    m_enviroment_settings.gateway[1] = (unsigned char) part[1];
    m_enviroment_settings.gateway[2] = (unsigned char) part[2];
    m_enviroment_settings.gateway[3] = (unsigned char) part[3];
}

unsigned short LJSettings::tcpCommandPort()
{
    return m_enviroment_settings.tcp_command_port;
}

void LJSettings::setTcpCommandPort(unsigned short port)
{
    m_enviroment_settings.tcp_command_port = port;
}

unsigned short LJSettings::tcpHighspeedPort()
{
    return m_enviroment_settings.tcp_highspeed_port;
}

void LJSettings::setTcpHighspeedPort(unsigned short port)
{

    m_enviroment_settings.tcp_highspeed_port = port;
}

MemoryAllocationOptions LJSettings::memoryAllocation()
{
    return (MemoryAllocationOptions) m_common.memory_allocation;
}

std::string LJSettings::memoryAllocationString()
{
    if(m_common.memory_allocation == 0)
        return "Double Buffer";
    else if(m_common.memory_allocation == 1)
        return "All areas";
    else
        return "?";
}

void LJSettings::setMemoryAllocation(MemoryAllocationOptions option)
{
    m_common.memory_allocation = option;
}

OperationWhenMemoryFullOptions LJSettings::operationWhenMemoryFull()
{
    return (OperationWhenMemoryFullOptions) m_common.operation_when_memory_full;
}

std::string LJSettings::operationWhenMemoryFullString()
{
    if(m_common.operation_when_memory_full == 0)
        return "Overwrite";
    else if(m_common.operation_when_memory_full == 1)
        return "Stop";
    else
        return "?";
}

void LJSettings::setOperationWhenMemoryFull(OperationWhenMemoryFullOptions operation)
{
    m_common.operation_when_memory_full = operation;
}

ParallelImagingOptions LJSettings::parallelImaging()
{
    return (ParallelImagingOptions) m_common.parallel_imaging;
}

std::string LJSettings::parallelImagingString()
{
    if(m_common.parallel_imaging == 0)
        return "Disabled";
    else if (m_common.parallel_imaging == 1)
        return "Enabled";
    else
        return "?";
}

void LJSettings::setParallelImaging(ParallelImagingOptions option)
{
    m_common.parallel_imaging = option;
}

TRGMinimumInputTimeOptions LJSettings::trgMinimumInputTime()
{
    return (TRGMinimumInputTimeOptions) m_common.trg_minimum_input_time;
}

std::string LJSettings::trgMinimumInputTimeString()
{
    switch(m_common.trg_minimum_input_time) {
    case 0:
        return "7us";
    case 1:
        return "10us";
    case 2:
        return "20us";
    case 3:
        return "50us";
    case 4:
        return "100us";
    case 5:
        return "200us";
    case 6:
        return "500us";
    case 7:
        return "1ms";
    default:
        return "?";
    }
}

void LJSettings::setTrgMinimumInputTime(TRGMinimumInputTimeOptions option)
{
    m_common.trg_minimum_input_time = option;
}

ENCODERMinimumInputTimeOptions LJSettings::encoderMinimumInputTime()
{
    return (ENCODERMinimumInputTimeOptions) m_common.encoder_minimum_input_time;
}

std::string LJSettings::encoderMinimumInputTimeString()
{
    switch(m_common.encoder_minimum_input_time) {
    case 0:
        return "120ns";
    case 1:
        return "150ns";
    case 2:
        return "250ns";
    case 3:
        return "500ns";
    case 4:
        return "1us";
    case 5:
        return "2us";
    case 6:
        return "5us";
    case 7:
        return "10us";
    case 8:
        return "20us";
    default:
        return "?";
    }
}

void LJSettings::setEncoderMinimumInputTime(ENCODERMinimumInputTimeOptions option)
{
    m_common.encoder_minimum_input_time = option;
}

ControlTerminalMinimumInputTimeOptions LJSettings::controlTerminalMinimumInputTime()
{
    return (ControlTerminalMinimumInputTimeOptions) m_common.control_terminal_minimum_input_time;
}

std::string LJSettings::controlTerminalMinimumInputTimeString()
{
    switch(m_common.control_terminal_minimum_input_time) {
    case 0:
        return "250us";
    case 1:
        return "1ms";
    default:
        return "?";
    }
}

void LJSettings::setControlTerminalMinimumInputTime(ControlTerminalMinimumInputTimeOptions option)
{
    m_common.control_terminal_minimum_input_time = option;
}

BrightnessOutputOptions LJSettings::brightnessOutput()
{
    return (BrightnessOutputOptions) m_common.brightness_output;
}

std::string LJSettings::brightnessOutputString()
{
    if(m_common.brightness_output == 0)
        return "Height Data Only";
    else
        return "Height+Brightness data";
}

void LJSettings::setBrightnessOutput(BrightnessOutputOptions option)
{
    m_common.brightness_output = option;
}

TriggerModeOptions LJSettings::triggerMode(int program)
{
    return (TriggerModeOptions)m_programms[program].triggerMode;
}

std::string LJSettings::triggerModeString(int program)
{
    switch(triggerMode(program)) {
    case(TriggerMode_Continuous):
        return "Continuous";
    case(TriggerMode_External):
        return "External";
    case(TriggerMode_Encoder):
        return "Encoder";
    default:
        return "INVALID";
    }
}

void LJSettings::setTriggerMode(TriggerModeOptions option, int program)
{
    m_programms[program].triggerMode = option;
}

SamplingCycleOptions LJSettings::samplingCycle(int program)
{
    return (SamplingCycleOptions)m_programms[program].samplingCycle;
}

std::string LJSettings::samplingCycleString(int program)
{
    if(isLJX(m_sensor)) {
        switch(samplingCycle(program)) {
        case SamplingCycleLJX_10Hz:
            return "10Hz";
        case SamplingCycleLJX_20Hz:
            return "20Hz";
        case SamplingCycleLJX_50Hz:
            return "50Hz";
        case SamplingCycleLJX_100Hz:
            return "100Hz";
        case SamplingCycleLJX_200Hz:
            return "200Hz";
        case SamplingCycleLJX_500Hz:
            return "500Hz";
        case SamplingCycleLJX_1KHz:
            return "1KHz";
        case SamplingCycleLJX_2KHz:
            return "2KHz";
        case SamplingCycleLJX_4KHz:
            return "4KHz";
        case SamplingCycleLJX_8KHz:
            return "8KHz";
        case SamplingCycleLJX_16KHz:
            return "16KHz";
        default:
            return "INVALID";
        }
    } else if(isLJV(m_sensor)) {
        switch(samplingCycle()) {
        case SamplingCycleLJV_10Hz:
            return "10Hz";
        case SamplingCycleLJV_20Hz:
            return "20Hz";
        case SamplingCycleLJV_50Hz:
            return "50Hz";
        case SamplingCycleLJV_100Hz:
            return "100Hz";
        case SamplingCycleLJV_200Hz:
            return "200Hz";
        case SamplingCycleLJV_500Hz:
            return "500Hz";
        case SamplingCycleLJV_1KHz:
            return "1KHz";
        case SamplingCycleLJV_2KHz:
            return "2KHz";
        case SamplingCycleLJV_4KHz:
            return "4KHz";
        case SamplingCycleLJV_4K13Hz:
            return "4.13KHz";
        case SamplingCycleLJV_8KHz:
            return "8KHz";
        case SamplingCycleLJV_16KHz:
            return "16KHz";
        case SamplingCycleLJV_32KHz:
            return "32KHz";
        case SamplingCycleLJV_64KHz:
            return "64KHz";
        default:
            return "INVALID";
        }
    } else {
        return "INVALID";
    }
}

void LJSettings::setSamplingCycle(SamplingCycleOptions option, int program)
{
    m_programms[program].samplingCycle = option;
}

BatchMeasurementOptions LJSettings::batchMeasurement(int program)
{
    return (BatchMeasurementOptions)m_programms[program].batchMeasurement;
}

std::string LJSettings::batchMeasurementString(int program)
{
    switch(batchMeasurement(program)) {
    case BatchMeasurementBatch_OFF:
        return "OFF";
    case BatchMeasurementBatch_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setBatchMeasurement(BatchMeasurementOptions option, int program)
{
    m_programms[program].batchMeasurement = option;
}

unsigned short LJSettings::batchCount(int program)
{
    return m_programms[program].batchCount;
}

void LJSettings::setBatchCount(unsigned short option, int program)
{
    m_programms[program].batchCount = option;
}

InterTriggerPitchOptions LJSettings::interTriggerPitch(int program)
{
    return (InterTriggerPitchOptions)m_programms[program].interTriggerPitch;
}

std::string LJSettings::interTriggerPitchString(int program)
{
    switch(interTriggerPitch(program)) {
    case InterTriggerPitch_OFF:
        return "OFF";
    case InterTriggerPitch_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setInterTriggerPitch(InterTriggerPitchOptions option, int program)
{
    m_programms[program].interTriggerPitch = option;
}

unsigned long LJSettings::interTriggerPitchCount(int program)
{
    return m_programms[program].interTriggerPitchCount;
}

std::string LJSettings::interTriggerPitchCountString(int program)
{
    double r = interTriggerPitchCount(program) / 10000;
    return std::to_string(r);
}

void LJSettings::setInterTriggerPitchCount(unsigned long option, int program)
{
    m_programms[program].interTriggerPitchCount = option;
}

SynchronizationOfMultipleControllersOptions LJSettings::synchronization(int program)
{
    return (SynchronizationOfMultipleControllersOptions)m_programms[program].synchronization;
}

std::string LJSettings::synchronizationString(int program)
{
    switch(synchronization(program)) {
    case(SynchronizationOfMultipleControllers_OFF):
        return "OFF";
    case SynchronizationOfMultipleControllers_Master:
        return "MASTER";
    case SynchronizationOfMultipleControllers_Slave:
        return "SLAVE";
    default:
        return "INVALID";
    }
}

void LJSettings::setSynchronizatiuon(SynchronizationOfMultipleControllersOptions option, int program)
{
    m_programms[program].synchronization = option;
}

MutualInterferencePreventionOptions LJSettings::mutualInterferencePrevention(int program)
{
    return (MutualInterferencePreventionOptions)m_programms[program].mutualInterferencePrevention;
}

std::string LJSettings::mutualInterferencePreventionString(int program)
{
    switch(mutualInterferencePrevention(program)) {
    case(MutualInterferencePrevention_OFF):
        return "OFF";
    case(MutualInterferencePrevention_ON):
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setMutualInterferencePrevention(MutualInterferencePreventionOptions option, int program)
{
    m_programms[program].mutualInterferencePrevention = option;
}

MutualInterferencePreventionSlaveEmissionOptions LJSettings::mutualInterferencePreventionSlaveEmission(int program)
{
    return (MutualInterferencePreventionSlaveEmissionOptions)m_programms[program].mutualInterferencePreventionSlaveEmission;
}

std::string LJSettings::mutualInterferencePreventionSlaveEmissionString(int program)
{
    switch(mutualInterferencePreventionSlaveEmission(program)) {
    case(MutualInterferencePreventionSlaveEmission_SameAsMaster):
        return "SameAsMaster";
    case(MutualInterferencePreventionSlaveEmission_AlterningWithTheMaster):
        return "AlterningWithTheMaster";
    default:
        return "INVALID";
    }
}

void LJSettings::setMutualInterferencePreventionSlaveEmission(MutualInterferencePreventionSlaveEmissionOptions option, int program)
{
    m_programms[program].mutualInterferencePreventionSlaveEmission = option;
}

EncoderInputModeOptions LJSettings::encoderInputMode(int program)
{
    return (EncoderInputModeOptions)m_programms[program].encoderInputMode;
}

std::string LJSettings::encoderInputModeString(int program)
{
    switch(encoderInputMode(program)) {
    case(EncoderTriggerInputMode_1Phase1Time):
        return "1-phase 1 time (no direction)";
    case(EncoderTriggerInputMode_2Phase1Time):
        return "2-phase 1 time";
    case(EncoderTriggerInputMode_2Phase2Times):
        return "2-phase 2 time";
    case(EncoderTriggerInputMode_2Phase4Times):
        return "2-phase 4 time";
    default:
        return "INVALID";
    }
}

void LJSettings::setEncoderInputMode(EncoderInputModeOptions option, int program)
{
    m_programms[program].encoderInputMode = option;
}

SubSamplingOptions LJSettings::subSamplingOptions(int program)
{
    return (SubSamplingOptions)m_programms[program].subSamplingOptions;
}

std::string LJSettings::subSamplingOptionsString(int program)
{
    switch(subSamplingOptions(program)) {
    case(SubSampling_OFF):
        return "OFF";
    case(SubSampling_ON):
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setSubSamplingOptions(SubSamplingOptions option, int program)
{
    m_programms[program].subSamplingOptions = (unsigned char) option;
}

unsigned short LJSettings::pointsToSubSample(int program)
{
    return m_programms[program].pointsToSubSample;
}

void LJSettings::setPointsToSubSample(unsigned short option, int program)
{
    m_programms[program].pointsToSubSample = option;
}

BinningOptions LJSettings::binning(int program)
{
    return (BinningOptions)m_programms[program].binning;
}

std::string LJSettings::binningString(int program)
{
    switch(binning(program)) {
    case Binning_OFF:
        return "OFF";
    case Binning_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setBinning(BinningOptions option, int program)
{
    m_programms[program].binning = option;
}

MeasurementRangeXDirectionOptions LJSettings::measurementRangeXDirection(int program)
{
    return (MeasurementRangeXDirectionOptions)m_programms[program].measurementRangeXDirection;
}

std::string LJSettings::measurementRangeXDirectionString(int program)
{
    if(isLJV(m_sensor)) {
        switch(measurementRangeXDirection(program)) {
        case MeasurementRangeXDirectionLJV_FULL:
            return "FULL";
        case MeasurementRangeXDirectionLJV_MIDDLE:
            return "MIDDLE";
        case MeasurementRangeXDirectionLJV_SMALL:
            return "SMALL";
        default:
            return "INVALID";
        }
    } else if(isLJX(m_sensor)) {
        switch(measurementRangeXDirection(program)) {
        case MeasurementRangeXDirectionLJX_FULL:
            return "FULL";
        case MeasurementRangeXDirectionLJX_ThreeQuarters:
            return "3/4";
        case MeasurementRangeXDirectionLJX_OneAndHalf:
            return "1/2";
        case MeasurementRangeXDirectionLJX_OneQuarter:
            return "1/4";
        default:
            return "INVALID";
        }
    } else {
        return "INVALID";
    }
}

void LJSettings::setMeasuremenetRangeXDirection(MeasurementRangeXDirectionOptions option, int program)
{
    m_programms[program].measurementRangeXDirection = option;
}

unsigned short LJSettings::measurementRangeXDirectionCenter(int program)
{
    return m_programms[program].measurementRangeXDirectionCenter;
}

std::string LJSettings::measurementRangeXDirectionCenterString(int program)
{
    return std::to_string(measurementRangeXDirectionCenter(program)/10.0);
}

void LJSettings::setMeasurementRangeXDirectionCenter(unsigned short option, int program)
{
    m_programms[program].measurementRangeXDirectionCenter = option;
}

MeasurementRangeZDirectionOptions LJSettings::measurementRangeZDirection(int program)
{
    return (MeasurementRangeZDirectionOptions)m_programms[program].measurementRangeZDirection;
}

std::string LJSettings::measurementRangeZDirectionString(int program)
{
    if(isLJV(m_sensor)) {
        switch(measurementRangeZDirection(program)) {
        case MeasurementRangeZDirectionLJV_FULL:
            return "FULL";
        case MeasurementRangeZDirectionLJV_MIDDLE:
            return "MIDDLE";
        case MeasurementRangeZDirectionLJV_SMALL:
            return "SMALL";
        default:
            return "INVALID";
        }
    } else if(isLJX(m_sensor)) {
        switch(measurementRangeZDirection(program)) {
        case MeasurementRangeZDirectionLJX_FULL:
            return "FULL";
        case MeasurementRangeZDirectionLJX_OneAndHalf:
            return "1/2";
        case MeasurementRangeZDirectionLJX_OneQuarter:
            return "1/4";
        case MeasurementRangeZDirectionLJX_OneEighth:
            return "1/8";
        case MeasurementRangeZDirectionLJX_OneSixteenth:
            return "1/16";
        case MeasurementRangeZDirectionLJX_OneThirtyTwo:
            return "1/32";
        default:
            return "INVALID";
        }
    } else {
        return "INVALID";
    }
}

void LJSettings::setMeasurementRangeZDirection(MeasurementRangeZDirectionOptions option, int program)
{
    m_programms[program].measurementRangeZDirection = option;
}

unsigned short LJSettings::measurementRangeZDirectionCenter(int program)
{
    return m_programms[program].measurementRangeZDirectionCenter;
}

std::string LJSettings::measurementRangeZDirectionCenterString(int program)
{
    return std::to_string(measurementRangeZDirectionCenter(program)/10.0);
}

void LJSettings::setMeasurementRangeZDirectionCenter(unsigned short option, int program)
{
    m_programms[program].measurementRangeZDirectionCenter = option;
}

MeasurementRangeZDirectionBinningOptions LJSettings::measurementRangeZDirectionBinning(int program)
{
    return (MeasurementRangeZDirectionBinningOptions)m_programms[program].measurementRangeZDirectionBinning;
}

std::string LJSettings::measurementRangeZDirectionBinningString(int program)
{
    switch(measurementRangeZDirectionBinning(program)) {
    case MeasurementRangeZDirectionBinning_OFF:
        return "OFF";
    case MeasurementRangeZDirectionBinning_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setMeasurementRangeZDirectionBinning(MeasurementRangeZDirectionBinningOptions option, int program)
{
    m_programms[program].measurementRangeZDirectionBinning = option;
}

unsigned char LJSettings::dynamicRange(int program)
{
    return m_programms[program].dynamicRange;
}

std::string LJSettings::dynamicRangeString(int program)
{
    if(isLJX(m_sensor)) {
        return std::to_string(measurementRangeZDirectionBinning(program));
    } else if (isLJV(m_sensor)) {
        switch(dynamicRange(program)) {
        case 0:
            return "High accuracy";
        case 1:
            return "High dynamic range 1";
        case 2:
            return "High dynamic range 2";
        case 3:
            return "High dynamic range 3";
        default:
            return "INVALID";
        }
    } else {
        return "INVALID";
    }
}

void LJSettings::setDynamicRange(unsigned char option, int program)
{
    m_programms[program].dynamicRange = option;
}

ExposureTimeOptions LJSettings::exposureTime(int program)
{
    return (ExposureTimeOptions)m_programms[program].exposureTime;
}

std::string LJSettings::exposureTimeString(int program)
{
    if(isLJX(m_sensor)) {
        switch(exposureTime(program)) {
        case ExposureTimeLJX_15us:
            return "15μs";
        case ExposureTimeLJX_30us:
            return "30μs";
        case ExposureTimeLJX_60us:
            return "60μs";
        case ExposureTimeLJX_120us:
            return "120μs";
        case ExposureTimeLJX_240us:
            return "240μs";
        case ExposureTimeLJX_480us:
            return "480μs";
        case ExposureTimeLJX_960us:
            return "960μs";
        case ExposureTimeLJX_1700us:
            return "1700μs";
        case ExposureTimeLJX_4ms8:
            return "4.8ms";
        case ExposureTimeLJX_9ms6:
            return "9.6ms";
        default:
            return "INVALID";
        }
    } else if(isLJV(m_sensor)) {
        switch(exposureTime(program)) {
        case ExposureTimeLJV_15us:
            return "15μs";
        case ExposureTimeLJV_30us:
            return "30μs";
        case ExposureTimeLJV_60us:
            return "60μs";
        case ExposureTimeLJV_120us:
            return "120μs";
        case ExposureTimeLJV_240us:
            return "240μs";
        case ExposureTimeLJV_480us:
            return "480μs";
        case ExposureTimeLJV_960us:
            return "960μs";
        case ExposureTimeLJV_1920us:
            return "1920μs";
        case ExposureTimeLJV_5ms:
            return "5ms";
        case ExposureTimeLJV_10ms:
            return "10ms";
        default:
            return "INVALID";
        }
    } else {
        return "INVALID";
    }
}

void LJSettings::setExposureTime(ExposureTimeOptions option, int program)
{
    m_programms[program].exposureTime = option;
}

ExposureModeOptions LJSettings::exposureMode(int program)
{
    return (ExposureModeOptions)m_programms[program].exposureMode;
}

std::string LJSettings::exposureModeString(int program)
{
    switch(exposureMode(program)) {
    case ExposureMode_Standard:
        return "Standard";
    case ExposureMode_MultiEmissionSynthesis:
        return "MultiEmissionSynthesis";
    case ExposureMode_MultiEmissionOptimizedLightIntensity:
        return "MultiEmissionOptimizedLightIntensity";
    default:
        return "INVALID";
    }
}

void LJSettings::setExposureMode(ExposureModeOptions option, int program)
{
    m_programms[program].exposureMode = option;
}

MultiEmissionDetailsOptimizedLightIntensityOptions LJSettings::multiEmissionDetailsOptimizedLightIntensity(int program)
{
    return (MultiEmissionDetailsOptimizedLightIntensityOptions)m_programms[program].multiEmissionDetailsOptimizedLightIntensity;
}

std::string LJSettings::multiEmissionDetailsOptimizedLightIntensityString(int program)
{
    switch(multiEmissionDetailsOptimizedLightIntensity(program)) {
    case MultiEmissionDetailsOptimizedLightIntensity_Two:
        return "2";
    case MultiEmissionDetailsOptimizedLightIntensity_Four:
        return "4";
    default:
        return "INVALID";
    }
}

void LJSettings::setMultiEmissionDetailsOptimizedLightIntensity(MultiEmissionDetailsOptimizedLightIntensityOptions option, int program)
{
    m_programms[program].multiEmissionDetailsOptimizedLightIntensity = option;
}

MultiEmissionDetailsSynthesisOptions LJSettings::multiEmissionSynthesis(int program)
{
    return (MultiEmissionDetailsSynthesisOptions)m_programms[program].multiEmissionSynthesis;
}

std::string LJSettings::multiEmissionSynthesisString(int program)
{
    switch(multiEmissionSynthesis(program)){
    case MultiEmissionDetailsSynthesis_Three:
        return "3";
    case MultiEmissionDetailsSynthesis_Five:
        return "5";
    default:
        return "INVALID";
    }
}

void LJSettings::setMultiEmissionSynthesis(MultiEmissionDetailsSynthesisOptions option, int program)
{
    m_programms[program].multiEmissionSynthesis = option;
}

MaskSettingOptions LJSettings::maskSettings(int program)
{
    return (MaskSettingOptions)m_programms[program].maskSettingsLower1Enabled;
}

void LJSettings::setMaskSettings(MaskSettingOptions option, int program)
{
    m_programms[program].maskSettingsLower1Enabled = option;
}

unsigned short LJSettings::maskSettingsXCoordinate1(int program)
{
    return m_programms[program].maskSettingsLower1XCoordinate1;
}

void LJSettings::setMaskSettingsXCoordinate1(unsigned short option, int program)
{
    m_programms[program].maskSettingsLower1XCoordinate1 = option;
}

unsigned short LJSettings::maskSettingsZCoordinate1(int program)
{
    return m_programms[program].maskSettingsLower1ZCoordinate1;
}

void LJSettings::setMaskSettingsZCoordinate1(unsigned short option, int program)
{
    m_programms[program].maskSettingsLower1ZCoordinate1 = option;
}

unsigned short LJSettings::maskSettingsXCoordinate2(int program)
{
    return m_programms[program].maskSettingsLower1XCoordinate2;
}

void LJSettings::setMaskSettingsXCoordinate2(unsigned short option, int program)
{
    m_programms[program].maskSettingsLower1XCoordinate2 = option;
}

unsigned short LJSettings::maskSettingsZCoordinate2(int program)
{
    return m_programms[program].maskSettingsLower1ZCoordinate2;
}

void LJSettings::setMaskSettingsZCoordinate2(unsigned short option, int program)
{
    m_programms[program].maskSettingsLower1ZCoordinate2 = option;
}

unsigned short LJSettings::maskSettingsXCoordinate3(int program)
{
    return m_programms[program].maskSettingsLower1XCoordinate3;
}

void LJSettings::setMaskSettingsXCoordinate3(unsigned short option, int program)
{
    m_programms[program].maskSettingsLower1XCoordinate3 = option;
}

unsigned short LJSettings::maskSettingsZCoordinate3(int program)
{
    return m_programms[program].maskSettingsLower1ZCoordinate3;
}

void LJSettings::setMaskSettingsZCoordinate3(unsigned short option, int program)
{
    m_programms[program].maskSettingsLower1ZCoordinate3 = option;
}

LightIntensityControlModeOptions LJSettings::lightIntensityControlMode(int program)
{
    return (LightIntensityControlModeOptions)m_programms[program].lightIntensityControlMode;
}

std::string LJSettings::lightIntensityControlModeString(int program)
{
    switch(lightIntensityControlMode(program)) {
    case LightIntensityControlMode_AUTO:
        return "AUTO";
    case LightIntensityControlMode_MANUAL:
        return "MANUAL";
    default:
        return "INVALID";
    }
}

void LJSettings::setLightIntensityControlMode(LightIntensityControlModeOptions option, int program)
{
    m_programms[program].lightIntensityControlMode = option;
}

unsigned char LJSettings::lightIntensityUpperLimit(int program)
{
    return m_programms[program].lightIntensityUpperLimit;
}

void LJSettings::setLightIntensityUpperLimit(unsigned char option, int program)
{
    m_programms[program].lightIntensityUpperLimit = option;
}

unsigned char LJSettings::lightIntensityLowerLimit(int program)
{
    return m_programms[program].lightIntensityLowerLimit;
}

void LJSettings::setLightIntensityLowerLimit(unsigned char option, int program)
{
    m_programms[program].lightIntensityLowerLimit = option;
}

unsigned short LJSettings::lightIntensityControlTargetAreaStart(int program)
{
    return m_programms[program].lightIntensityControlTargetAreaStart;
}

std::string LJSettings::lightIntensityControlTargetAreaStartString(int program)
{
    return std::to_string(lightIntensityControlTargetAreaStart(program)/10.0);
}

void LJSettings::setLightIntensityControlTargetAreaStart(unsigned short option, int program)
{
    m_programms[program].lightIntensityControlTargetAreaStart = option;
}

unsigned short LJSettings::lightIntensityControlTargetAreaStop(int program)
{
    return m_programms[program].lightIntensityControlTargetAreaStop;
}

std::string LJSettings::lightIntensityControlTargetAreaStopString(int program)
{
    return std::to_string(lightIntensityControlTargetAreaStop(program)/10.0);
}

void LJSettings::setLightIntensityControlTargetAreaStop(unsigned short option, int program)
{
    m_programms[program].lightIntensityControlTargetAreaStop = option;
}

unsigned char LJSettings::peakDetectionSensitivity(int program)
{
    return m_programms[program].peakDetectionSensitivity;
}

void LJSettings::setPeakDetectionSensitivity(unsigned char option, int program)
{
    m_programms[program].peakDetectionSensitivity = option;
}

unsigned char LJSettings::invalidDataInterpolationCount(int program)
{
    return m_programms[program].invalidDataInterpolationCount;
}

void LJSettings::setInvalidDataInterpolationCount(unsigned char option, int program)
{
    m_programms[program].invalidDataInterpolationCount = option;
}

PeakSelectionOptions LJSettings::peakSelection(int program)
{
    return (PeakSelectionOptions)m_programms[program].peakSelection;
}

std::string LJSettings::peakSelectionString(int program)
{
    if(isLJX(m_sensor)) {
        switch(peakSelection(program)) {
        case PeakSelectionLJX_Standard:
            return "Standard";
        case PeakSelectionLJX_FAR:
            return "FAR";
        case PeakSelectionLJX_NEAR:
            return "NEAR";
        case PeakSelectionLJX_INVALID:
            return "Make INVALID data";
        default:
            return "INVALID";
        }
    } else if(isLJV(m_sensor)) {
        switch(peakSelection(program)) {
        case PeakSelectionLJV_Standard:
            return "Standard";
        case PeakSelectionLJV_NEAR:
            return "NEAR";
        case PeakSelectionLJV_FAR:
            return "FAR";
        case PeakSelectionLJV_RemoveXMultiReflection:
            return "Remove X multi reflection";
        case PeakSelectionLJV_RemoveYMultiReflection:
            return "Remove Y multi reflection";
        case PeakSelectionLJV_INVALID:
            return "Make INVALID data";
        default:
            return "INVALID";
        }
    } else
        return "INVLALID";
}

void LJSettings::setPeakSelection(PeakSelectionOptions option, int program)
{
    m_programms[program].peakSelection = option;
}

PeakWidthFilterOptions LJSettings::peakWidthFilter(int program)
{
    return (PeakWidthFilterOptions)m_programms[program].peakWidthFilter;
}

std::string LJSettings::peakWidthFilterString(int program)
{
    switch(peakWidthFilter(program)) {
    case PeakWidthFilter_OFF:
        return "OFF";
    case PeakWidthFilter_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setPeakWidthFilter(PeakWidthFilterOptions option, int program)
{
    m_programms[program].peakWidthFilter = option;
}

unsigned char LJSettings::peakWidthFilterStrength(int program)
{
    return m_programms[program].peakWidthFilterStrength;
}

void LJSettings::setPeakWidthFilterStrength(unsigned char option, int program)
{
    m_programms[program].peakWidthFilterStrength = option;
}

StrayLightSuppressionFunctionOptions LJSettings::strayLightSuppressionFunction(int program)
{
    return (StrayLightSuppressionFunctionOptions)m_programms[program].strayLightSuppressionFunction;
}

std::string LJSettings::strayLightSuppressionFunctionString(int program)
{
    switch(strayLightSuppressionFunction(program)) {
    case StrayLightSuppressionFunction_OFF:
        return "OFF";
    case StrayLightSuppressionFunction_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setStrayLightSuppressionFunction(StrayLightSuppressionFunctionOptions option, int program)
{
    m_programms[program].strayLightSuppressionFunction = option;
}

unsigned char LJSettings::strayLightSuppressionFunctionFilterStrength(int program)
{
    return m_programms[program].strayLightSuppressionFunctionFilterStrength;
}

void LJSettings::setStrayLightSuppressionFunctionFilterStrength(unsigned char option, int program)
{
    m_programms[program].strayLightSuppressionFunctionFilterStrength = option;
}

SubSamplingXAxisOptions LJSettings::subSamplingXAxis(int program)
{
    return (SubSamplingXAxisOptions)m_programms[program].subSamplingXAxis;
}

std::string LJSettings::subSamplingXAxisString(int program)
{
    switch(subSamplingXAxis(program)) {
    case SubSamplingXAxis_OFF:
        return "OFF";
    case SubSamplingXAxis_OneAndHalf:
        return "1/2";
    case SubSamplingXAxis_OneQuarter:
        return "1/4";
    default:
        return "INVALID";
    }
}

void LJSettings::setSubSamplingXAxis(SubSamplingXAxisOptions option, int program)
{
    m_programms[program].subSamplingXAxis = option;
}

DeadZoneDataInterpolationOptions LJSettings::deadZoneDataInterpolation(int program)
{
    return (DeadZoneDataInterpolationOptions)m_programms[program].deadZoneDataInterpolation;
}

std::string LJSettings::deadZoneDataInterpolationString(int program)
{
    switch(deadZoneDataInterpolation(program)) {
    case DeadZoneDataInterpolation_NoInterpolation:
        return "No interpolation";
    case DeadZoneDataInterpolation_LinearInterpolation:
        return "Linear interpolation";
    case DeadZoneDataInterpolation_VerticalInterpolation:
        return "Vertical Interpolation";
    default:
        return "INVALID";
    }
}

void LJSettings::setDeadZoneDataInterpolation(DeadZoneDataInterpolationOptions option, int program)
{
    m_programms[program].deadZoneDataInterpolation = option;
}

ReverseXOptions LJSettings::reverseX(int program)
{
    return (ReverseXOptions)m_programms[program].reverseX;
}

std::string LJSettings::reverseXString(int program)
{
    switch(reverseX(program)) {
    case ReverseX_OFF:
        return "OFF";
    case ReverseX_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setReverseX(ReverseXOptions option, int program)
{
    m_programms[program].reverseX = option;
}

ReverseZOptions LJSettings::reverseZ(int program)
{
    return (ReverseZOptions)m_programms[program].reverseZ;
}

std::string LJSettings::reverseZString(int program)
{
    switch(reverseZ(program)) {
    case ReverseZ_OFF:
        return "OFF";
    case ReverseZ_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setReverseZ(ReverseZOptions option, int program)
{
    m_programms[program].reverseZ = option;
}

signed int LJSettings::shiftX(int program)
{
    return m_programms[program].shiftX;
}

void LJSettings::setShiftX(signed int option, int program)
{
    m_programms[program].shiftX = option;
}

signed int LJSettings::shiftZ(int program)
{
    return m_programms[program].shiftZ;
}

void LJSettings::setShiftZ(signed int option, int program)
{
    m_programms[program].shiftZ = option;
}

MedianXAxisOptions LJSettings::medianXAxis(int program)
{
    return (MedianXAxisOptions)m_programms[program].medianXAxis;
}

std::string LJSettings::medianXAxisString(int program)
{
    switch(medianXAxis(program)) {
    case MedianXAxis_OFF:
        return "OFF";
    case MedianXAxis_3:
        return "3";
    case MedianXAxis_5:
        return "5";
    case MedianXAxis_7:
        return "7";
    case MedianXAxis_9:
        return "9";
    case MedianXAxis_17:
        return "17";
    case MedianXAxis_25:
        return "25";
    case MedianXAxis_33:
        return "33";
    default:
        return "INVALID";
    }
}

void LJSettings::setMedianXAxis(MedianXAxisOptions option, int program)
{
    m_programms[program].medianXAxis = option;
}

MedianYAxisOptions LJSettings::medianYAxis(int program)
{
    return (MedianYAxisOptions)m_programms[program].medianYAxis;
}

std::string LJSettings::medianYAxisString(int program)
{
    switch(medianYAxis(program)) {
    case MedianYAxis_OFF:
        return "OFF";
    case MedianYAxis_3:
        return "3";
    case MedianYAxis_5:
        return "5";
    case MedianYAxis_7:
        return "7";
    case MedianYAxis_9:
        return "9";
    default:
        return "INVALID";
    }
}

void LJSettings::setMedianYAxis(MedianYAxisOptions option, int program)
{
    m_programms[program].medianYAxis = option;
}

SmoothingCountOptions LJSettings::smoothing(int program)
{
    return (SmoothingCountOptions)m_programms[program].smoothing;
}

std::string LJSettings::smoothingString(int program)
{
    switch(smoothing(program)) {
    case SmoothingCount_1:
        return "1";
    case SmoothingCount_2:
        return "2";
    case SmoothingCount_4:
        return "4";
    case SmoothingCount_8:
        return "8";
    case SmoothingCount_16:
        return "16";
    case SmoothingCount_32:
        return "32";
    case SmoothingCount_64:
        return "64";
    default:
        return "INVALID";
    }
}

void LJSettings::setSmoothing(SmoothingCountOptions option, int program)
{
    m_programms[program].smoothing = option;
}

AveragingOptions LJSettings::averagingCount(int program)
{
    return (AveragingOptions)m_programms[program].averagingCount;
}

std::string LJSettings::averagingCountString(int program)
{
    switch(averagingCount(program)) {
    case Averaging_1:
        return "1";
    case Averaging_2:
        return "2";
    case Averaging_4:
        return "4";
    case Averaging_8:
        return "8";
    case Averaging_16:
        return "16";
    case Averaging_32:
        return "32";
    case Averaging_64:
        return "64";
    case Averaging_128:
        return "128";
    case Averaging_256:
        return "256";
    default:
        return "INVALID";
    }
}

void LJSettings::setAveragingCount(AveragingOptions option, int program)
{
    m_programms[program].averagingCount = option;
}

unsigned char LJSettings::invalidDataProcessingYProcessCount(int program)
{
    return m_programms[program].invalidDataProcessingYProcessCount;
}

void LJSettings::setInvalidDataProcessingYProcessCount(unsigned char option, int program)
{
    m_programms[program].invalidDataProcessingYProcessCount = option;
}

unsigned char LJSettings::invalidDataProcessingYResumeCount(int program)
{
    return m_programms[program].invalidDataProcessingYResumeCount;
}

void LJSettings::setInvalidDataProcessingYResumeCount(unsigned char option, int program)
{
    m_programms[program].invalidDataProcessingYResumeCount = option;
}

TiltCorrectionOptions LJSettings::tiltCorrectionOnOff(int program)
{
    return (TiltCorrectionOptions)m_programms[program].tiltCorrectionOnOff;
}

std::string LJSettings::tiltCorrectionOnOffString(int program)
{
    switch(tiltCorrectionOnOff(program)) {
    case TiltCorrection_OFF:
        return "OFF";
    case TiltCorrection_ON:
        return "ON";
    default:
        return "INVALID";
    }
}

void LJSettings::setTiltCorrectionOnOff(TiltCorrectionOptions option, int program)
{
    m_programms[program].tiltCorrectionOnOff = option;
}

unsigned char LJSettings::tiltCorrectionLineCalculationAreaCount(int program)
{
    return m_programms[program].tiltCorrectionLineCalculationAreaCount;
}

std::string LJSettings::tiltCorrectionLineCalculationAreaCountString(int program)
{
    return std::to_string( tiltCorrectionLineCalculationAreaCount(program));
}

void LJSettings::setTiltCorrectionLineCalculationAreaCount(unsigned char option, int program)
{
    m_programms[program].tiltCorrectionLineCalculationAreaCount = option;
}

signed int LJSettings::tiltCorrectionAreaStartPosition1(int program)
{
    return m_programms[program].tiltCorrectionAreaStartPosition1;
}

void LJSettings::setTiltCorrectionAreaStartPosition1(signed int option, int program)
{
    m_programms[program].tiltCorrectionAreaStartPosition1 = option;
}

signed int LJSettings::tiltCorrectionAreaEndPosition1(int program)
{
    return m_programms[program].tiltCorrectionAreaEndPosition1;
}

void LJSettings::setTiltCorrectionAreaEndPosition1(signed int option, int program)
{
    m_programms[program].tiltCorrectionAreaEndPosition1 = option;
}

signed int LJSettings::tiltCorrectionAreaStartPosition2(int program)
{
    return m_programms[program].tiltCorrectionAreaStartPosition2;
}

void LJSettings::setTiltCorrectionAreaStartPosition2(signed int option, int program)
{
    m_programms[program].tiltCorrectionAreaStartPosition2 = option;
}

signed int LJSettings::tiltCorrectionAreaEndPosition2(int program)
{
    return m_programms[program].tiltCorrectionAreaEndPosition2;
}

void LJSettings::setTiltCorrectionAreaEndPosition2(signed int option, int program)
{
    m_programms[program].tiltCorrectionAreaEndPosition2 = option;
}

signed short LJSettings::tiltCorrectionPostCorrectionAngle(int program)
{
    return m_programms[program].tiltCorrectionPostCorrectionAngle;
}

void LJSettings::setTiltCorrectionPostCorrectionAngle(signed short option, int program)
{
    m_programms[program].tiltCorrectionPostCorrectionAngle = option;
}

signed short LJSettings::tiltCorrectionCorrectionAngle(int program)
{
    return m_programms[program].tiltCorrectionCorrectionAngle;
}

void LJSettings::setTiltCorrectionCorrectionAngle(signed short option, int program)
{
    m_programms[program].tiltCorrectionCorrectionAngle = option;
}

HeightCorectionOptions LJSettings::heightCorrectionOnOff(int program)
{
    return (HeightCorectionOptions)m_programms[program].heightCorrectionOnOff;
}

void LJSettings::setHeightCorrectionOnOff(HeightCorectionOptions option, int program)
{
    m_programms[program].heightCorrectionOnOff = option;
}

signed int LJSettings::heightCorrectionAreaStartPosition1(int program)
{
    return m_programms[program].heightCorrectionAreaStartPosition1;
}

void LJSettings::setHeightCorrectionAreaStartPosition1(signed int option, int program)
{
    m_programms[program].heightCorrectionAreaStartPosition1 = option;
}

signed int LJSettings::heightCorrectionAreaEndPosition1(int program)
{
    return m_programms[program].heightCorrectionAreaEndPosition1;
}

void LJSettings::setHeightCorrectionAreaEndPosition1(signed int option, int program)
{
    m_programms[program].heightCorrectionAreaEndPosition1 = option;
}

signed int LJSettings::heightCorrectionAreaStartPosition2(int program)
{
    return m_programms[program].heightCorrectionAreaStartPosition2;
}

void LJSettings::setHeightCorrectionAreaStartPosition2(signed int option, int program)
{
    m_programms[program].heightCorrectionAreaStartPosition2 = option;
}

signed int LJSettings::heightCorrectionAreaEndPosition2(int program)
{
    return m_programms[program].heightCorrectionAreaEndPosition2;
}

void LJSettings::setHeightCorrectionAreaEndPosition2(signed int option, int program)
{
    m_programms[program].heightCorrectionAreaEndPosition2 = option;
}

unsigned int LJSettings::heightCorrectionPostCorrectionHeight(int program)
{
    return m_programms[program].heightCorrectionPostCorrectionHeight;
}

void LJSettings::setHeightCorrectionPostCorrectionHeight(unsigned int option, int program)
{
    m_programms[program].heightCorrectionPostCorrectionHeight = option;
}

unsigned int LJSettings::heightCorrectionSpan(int program)
{
    return m_programms[program].heightCorrectionSpan;
}

void LJSettings::setHeightCorrectionSpan(unsigned int option, int program)
{
    m_programms[program].heightCorrectionSpan = option;
}

unsigned char LJSettings::activeProgram() const
{
    return m_active_program;
}

void LJSettings::setActiveProgram(unsigned char newActive_program)
{
    m_active_program = newActive_program;
}

std::string LJSettings::sensorSN()
{
    return m_sensor_sn;
}

void LJSettings::setSensorSN(char sn[])
{
    for(int i = 0; i < 16; i++) {
        m_sensor_sn[i] = sn[i];
    }
}

std::string LJSettings::controllerSN()
{
    return m_controller_sn;
}

void LJSettings::setControllerSN(char sn[])
{
    for(int i = 0; i < 16; i++) {
        m_controller_sn[i] = sn[i];
    }
}
