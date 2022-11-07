#ifndef LJSETTINGS_H
#define LJSETTINGS_H
#include <string>
#include "FibreLJXFile_global.h"
#include "ljsettings_structs.h"
#include <QByteArray>
class FIBRELJXFILE_EXPORT LJSettings
{
public:
    static bool isLJX(LJSensorType sensor);
    static bool isLJV(LJSensorType sensor);

    LJSettings();
    // Gibt alle Einstellungen auf der Standardtextausgabe aus.
    void print();
    // Gibt nur die Programausgaben auf der Standardtextausgabe. Wenn -1 ausgewählt wird, dann wird nur das bei der Messung aktive Programm ausgegeben.
    void printProgram(int program = -1);
    // Gibt den SensorTyp aus. Es ist nicht sichergestellt, das dieser richtig ist, da er nicht automatisch ausgelesen werden kann.
    LJSensorType sensor();


    //Environment Settings
    LJX8IF_ETHERNET_CONFIG ethernetConfig();

    std::string deviceName();
    std::string operationAtNextPowerOnString();
    void setDeviceName(std::string name);

    OperationAtNextPowerOnOptions operationAtNextPowerOn();
    void setOperationAtNextPowerOn(OperationAtNextPowerOnOptions option);

    HighSpeedCommunicationBandRestrictionOptions highSpeedCommunicationBandRestriction();
    std::string highSpeedCommunicationBandRestrictionString();
    void setHighSpeedCommunicationBandRestricton(HighSpeedCommunicationBandRestrictionOptions option);

    unsigned short mtuDuringHighSpeedCommunicaton();
    void setMtuDuringHighSpeedCommunication(unsigned short option);

    std::string ipAddress();
    void setIpAddress(std::string ip);

    std::string subnetMask();
    void setSubnetMask(std::string &mask);

    std::string gateway();
    void setGateway(std::string &gateway);

    unsigned short tcpCommandPort();
    void setTcpCommandPort(unsigned short port);

    unsigned short tcpHighspeedPort();
    void setTcpHighspeedPort(unsigned short port);

    // Common Settings
    MemoryAllocationOptions memoryAllocation();
    std::string memoryAllocationString();
    void setMemoryAllocation(MemoryAllocationOptions option);

    OperationWhenMemoryFullOptions operationWhenMemoryFull();
    std::string operationWhenMemoryFullString();
    void setOperationWhenMemoryFull(OperationWhenMemoryFullOptions operation);

    ParallelImagingOptions parallelImaging();
    std::string parallelImagingString();
    void setParallelImaging(ParallelImagingOptions option);

    TRGMinimumInputTimeOptions trgMinimumInputTime();
    std::string trgMinimumInputTimeString();
    void setTrgMinimumInputTime(TRGMinimumInputTimeOptions options);

    ENCODERMinimumInputTimeOptions encoderMinimumInputTime();
    std::string encoderMinimumInputTimeString();
    void setEncoderMinimumInputTime(ENCODERMinimumInputTimeOptions option);

    ControlTerminalMinimumInputTimeOptions controlTerminalMinimumInputTime();
    std::string controlTerminalMinimumInputTimeString();
    void setControlTerminalMinimumInputTime(ControlTerminalMinimumInputTimeOptions option);

    BrightnessOutputOptions brightnessOutput();
    std::string brightnessOutputString();
    void setBrightnessOutput(BrightnessOutputOptions option);

//Program
    //Trigger Settings
    TriggerModeOptions triggerMode(int program = 0);
    std::string triggerModeString(int program = 0);
    void setTriggerMode(TriggerModeOptions option, int program = 0);

    SamplingCycleOptions samplingCycle(int program = 0);
    std::string samplingCycleString(int program = 0);
    void setSamplingCycle(SamplingCycleOptions option, int program = 0);

    BatchMeasurementOptions batchMeasurement(int program = 0);
    std::string batchMeasurementString(int program = 0);
    void setBatchMeasurement(BatchMeasurementOptions option, int program = 0);

    unsigned short batchCount(int program = 0);
    void setBatchCount(unsigned short option, int program = 0);

    InterTriggerPitchOptions interTriggerPitch(int program = 0);
    std::string interTriggerPitchString(int program = 0);
    void setInterTriggerPitch(InterTriggerPitchOptions option, int program = 0);

    unsigned long interTriggerPitchCount(int program = 0);
    std::string interTriggerPitchCountString(int program = 0);
    void setInterTriggerPitchCount(unsigned long option, int program = 0);

    SynchronizationOfMultipleControllersOptions synchronization(int program = 0);
    std::string synchronizationString(int program = 0);
    void setSynchronizatiuon(SynchronizationOfMultipleControllersOptions option, int program = 0);

    MutualInterferencePreventionOptions mutualInterferencePrevention(int program = 0);
    std::string mutualInterferencePreventionString(int program = 0);
    void setMutualInterferencePrevention(MutualInterferencePreventionOptions option, int program = 0);

    MutualInterferencePreventionSlaveEmissionOptions mutualInterferencePreventionSlaveEmission(int program = 0);
    std::string mutualInterferencePreventionSlaveEmissionString(int program = 0);
    void setMutualInterferencePreventionSlaveEmission(MutualInterferencePreventionSlaveEmissionOptions option, int program = 0);

    EncoderInputModeOptions encoderInputMode(int program = 0);
    std::string encoderInputModeString(int program = 0);
    void setEncoderInputMode(EncoderInputModeOptions option, int program = 0);

    SubSamplingOptions subSamplingOptions(int program = 0);
    std::string subSamplingOptionsString(int program = 0);
    void setSubSamplingOptions(SubSamplingOptions option, int program = 0);

    unsigned short pointsToSubSample(int program = 0);
    void setPointsToSubSample(unsigned short option, int program = 0);

    // Imaging Settings
    BinningOptions binning(int program = 0);
    std::string binningString(int programm = 0);
    void setBinning(BinningOptions option, int program = 0);

    MeasurementRangeXDirectionOptions measurementRangeXDirection(int program = 0);
    std::string measurementRangeXDirectionString(int program = 0);
    void setMeasuremenetRangeXDirection(MeasurementRangeXDirectionOptions option, int program = 0);

    unsigned short measurementRangeXDirectionCenter(int program = 0);
    std::string measurementRangeXDirectionCenterString(int program = 0);
    void setMeasurementRangeXDirectionCenter(unsigned short option, int program = 0);

    MeasurementRangeZDirectionOptions measurementRangeZDirection(int program = 0);
    std::string measurementRangeZDirectionString(int program = 0);
    void setMeasurementRangeZDirection(MeasurementRangeZDirectionOptions option, int program = 0);

    unsigned short measurementRangeZDirectionCenter(int program = 0);
    std::string measurementRangeZDirectionCenterString(int program = 0);
    void setMeasurementRangeZDirectionCenter(unsigned short option, int program = 0);

    MeasurementRangeZDirectionBinningOptions measurementRangeZDirectionBinning(int program = 0);
    std::string measurementRangeZDirectionBinningString(int program = 0);
    void setMeasurementRangeZDirectionBinning(MeasurementRangeZDirectionBinningOptions option, int program = 0);

    unsigned char dynamicRange(int program = 0);
    std::string dynamicRangeString(int program = 0);
    void setDynamicRange(unsigned char option, int program = 0);

    ExposureTimeOptions exposureTime(int program = 0);
    std::string exposureTimeString(int program = 0);
    void setExposureTime(ExposureTimeOptions option, int program = 0);

    ExposureModeOptions exposureMode(int program = 0);
    std::string exposureModeString(int program = 0);
    void setExposureMode(ExposureModeOptions option, int program = 0);

    MultiEmissionDetailsOptimizedLightIntensityOptions multiEmissionDetailsOptimizedLightIntensity(int program = 0);
    std::string multiEmissionDetailsOptimizedLightIntensityString(int program = 0);
    void setMultiEmissionDetailsOptimizedLightIntensity(MultiEmissionDetailsOptimizedLightIntensityOptions option, int program = 0);

    MultiEmissionDetailsSynthesisOptions multiEmissionSynthesis(int program = 0);
    std::string multiEmissionSynthesisString(int program = 0);
    void setMultiEmissionSynthesis(MultiEmissionDetailsSynthesisOptions option, int program = 0);

    // TODO Mask Settings
    MaskSettingOptions maskSettings(int program = 0);
    void setMaskSettings(MaskSettingOptions option, int program = 0);
    unsigned short maskSettingsXCoordinate1(int program = 0);
    void setMaskSettingsXCoordinate1(unsigned short option, int program = 0);
    unsigned short maskSettingsZCoordinate1(int program = 0);
    void setMaskSettingsZCoordinate1(unsigned short option, int program = 0);
    unsigned short maskSettingsXCoordinate2(int program = 0);
    void setMaskSettingsXCoordinate2(unsigned short option, int program = 0);
    unsigned short maskSettingsZCoordinate2(int program = 0);
    void setMaskSettingsZCoordinate2(unsigned short option, int program = 0);
    unsigned short maskSettingsXCoordinate3(int program = 0);
    void setMaskSettingsXCoordinate3(unsigned short option, int program = 0);
    unsigned short maskSettingsZCoordinate3(int program = 0);
    void setMaskSettingsZCoordinate3(unsigned short option, int program = 0);
    // TODO ENDE
    LightIntensityControlModeOptions lightIntensityControlMode(int program = 0);
    std::string lightIntensityControlModeString(int program = 0);
    void setLightIntensityControlMode(LightIntensityControlModeOptions option, int program = 0);

    unsigned char lightIntensityUpperLimit(int program = 0);
    void setLightIntensityUpperLimit(unsigned char option, int program = 0);

    unsigned char lightIntensityLowerLimit(int program = 0);
    void setLightIntensityLowerLimit(unsigned char option, int program = 0);

    unsigned short lightIntensityControlTargetAreaStart(int program = 0);
    std::string lightIntensityControlTargetAreaStartString(int program = 0);
    void setLightIntensityControlTargetAreaStart(unsigned short option, int program = 0);

    unsigned short lightIntensityControlTargetAreaStop(int program = 0);
    std::string lightIntensityControlTargetAreaStopString(int program = 0);
    void setLightIntensityControlTargetAreaStop(unsigned short option, int program = 0);

    unsigned char peakDetectionSensitivity(int program = 0);
    void setPeakDetectionSensitivity(unsigned char option, int program = 0);

    unsigned char invalidDataInterpolationCount(int program = 0);
    void setInvalidDataInterpolationCount(unsigned char option, int program = 0);

    PeakSelectionOptions peakSelection(int program = 0);
    std::string peakSelectionString(int program);
    void setPeakSelection(PeakSelectionOptions option, int program = 0);

    PeakWidthFilterOptions peakWidthFilter(int program = 0);
    std::string peakWidthFilterString(int program);
    void setPeakWidthFilter(PeakWidthFilterOptions option, int program = 0);

    unsigned char peakWidthFilterStrength(int program = 0);
    void setPeakWidthFilterStrength(unsigned char option, int program = 0);

    StrayLightSuppressionFunctionOptions strayLightSuppressionFunction(int program = 0);
    std::string strayLightSuppressionFunctionString(int program);
    void setStrayLightSuppressionFunction(StrayLightSuppressionFunctionOptions option, int program = 0);

    unsigned char strayLightSuppressionFunctionFilterStrength(int program = 0);
    void setStrayLightSuppressionFunctionFilterStrength(unsigned char option, int program = 0);

    //Profile
    SubSamplingXAxisOptions subSamplingXAxis(int program = 0);
    std::string subSamplingXAxisString(int program);
    void setSubSamplingXAxis(SubSamplingXAxisOptions option, int program = 0);

    DeadZoneDataInterpolationOptions deadZoneDataInterpolation(int program = 0);
    std::string deadZoneDataInterpolationString(int program = 0);
    void setDeadZoneDataInterpolation(DeadZoneDataInterpolationOptions option, int program = 0);

    ReverseXOptions reverseX(int program = 0);
    std::string reverseXString(int program);
    void setReverseX(ReverseXOptions option, int program = 0);

    ReverseZOptions reverseZ(int program = 0);
    std::string reverseZString(int program);
    void setReverseZ(ReverseZOptions option, int program = 0);

    signed int shiftX(int program = 0);
    void setShiftX(signed int option, int program = 0);

    signed int shiftZ(int program = 0);
    void setShiftZ(signed int option, int program = 0);

    MedianXAxisOptions medianXAxis(int program = 0);
    std::string medianXAxisString(int program);
    void setMedianXAxis(MedianXAxisOptions option, int program = 0);

    MedianYAxisOptions medianYAxis(int program = 0);
    std::string medianYAxisString(int program);
    void setMedianYAxis(MedianYAxisOptions option, int program = 0);

    SmoothingCountOptions smoothing(int program = 0);
    std::string smoothingString(int program);
    void setSmoothing(SmoothingCountOptions option, int program = 0);

    AveragingOptions averagingCount(int program = 0);
    std::string averagingCountString(int program);
    void setAveragingCount(AveragingOptions option, int program = 0);

    unsigned char invalidDataProcessingYProcessCount(int program = 0);
    void setInvalidDataProcessingYProcessCount(unsigned char option, int program = 0);

    unsigned char invalidDataProcessingYResumeCount(int program = 0);
    void setInvalidDataProcessingYResumeCount(unsigned char option, int program = 0);

    TiltCorrectionOptions tiltCorrectionOnOff(int program = 0);
    std::string tiltCorrectionOnOffString(int program);
    void setTiltCorrectionOnOff(TiltCorrectionOptions option, int program = 0);

    unsigned char tiltCorrectionLineCalculationAreaCount(int program = 0);
    std::string tiltCorrectionLineCalculationAreaCountString(int program);
    void setTiltCorrectionLineCalculationAreaCount(unsigned char option, int program = 0);

    signed int tiltCorrectionAreaStartPosition1(int program = 0);
    void setTiltCorrectionAreaStartPosition1(signed int option, int program = 0);

    signed int tiltCorrectionAreaEndPosition1(int program = 0);
    void setTiltCorrectionAreaEndPosition1(signed int option, int program = 0);

    signed int tiltCorrectionAreaStartPosition2(int program = 0);
    void setTiltCorrectionAreaStartPosition2(signed int option, int program = 0);

    signed int tiltCorrectionAreaEndPosition2(int program = 0);
    void setTiltCorrectionAreaEndPosition2(signed int option, int program = 0);

    signed short tiltCorrectionPostCorrectionAngle(int program = 0);
    void setTiltCorrectionPostCorrectionAngle(signed short option, int program = 0);

    signed short tiltCorrectionCorrectionAngle(int program = 0);
    void setTiltCorrectionCorrectionAngle(signed short option, int program = 0);

    HeightCorectionOptions heightCorrectionOnOff(int program = 0);
    void setHeightCorrectionOnOff(HeightCorectionOptions option, int program = 0);
    signed int heightCorrectionAreaStartPosition1(int program = 0);
    void setHeightCorrectionAreaStartPosition1(signed int option, int program = 0);
    signed int heightCorrectionAreaEndPosition1(int program = 0);
    void setHeightCorrectionAreaEndPosition1(signed int option, int program = 0);
    signed int heightCorrectionAreaStartPosition2(int program = 0);
    void setHeightCorrectionAreaStartPosition2(signed int option, int program = 0);
    signed int heightCorrectionAreaEndPosition2(int program = 0);
    void setHeightCorrectionAreaEndPosition2(signed int option, int program = 0);
    unsigned int heightCorrectionPostCorrectionHeight(int program = 0);
    void setHeightCorrectionPostCorrectionHeight(unsigned int option, int program = 0);
    unsigned int heightCorrectionSpan(int program = 0);
    void setHeightCorrectionSpan(unsigned int option, int program = 0);
    unsigned char activeProgram() const;
    void setActiveProgram(unsigned char newActive_program);

    std::string sensorSN();
    void setSensorSN(char sn[]);

    std::string controllerSN();
    void setControllerSN(char sn[]);

    // Funktionen für die Schnittstelle zum Highspeed-SDK eher nicht für dich gedacht.
    QByteArray getData();
    void setData(QByteArray &data);
    LJX8IF_TARGET_SETTING getTargetSetting(Parameter param, unsigned char program = 0x00);
    void setSettingRaw(LJX8IF_TARGET_SETTING target, char data[], int length);
private:
    char m_sensor_sn[16];
    char m_controller_sn[16];
    CommonSettings m_common;
    EnviromentSettings m_enviroment_settings;
    Program m_programms[16];
    unsigned char m_active_program = 0;
    LJSensorType m_sensor = LJ_X8080;
};

#endif // LJSETTINGS_H
