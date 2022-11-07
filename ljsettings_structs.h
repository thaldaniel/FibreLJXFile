#ifndef LJSETTINGS_STRUCTS_H
#define LJSETTINGS_STRUCTS_H
#include <windows.h>

struct CommonSettings {
    unsigned char memory_allocation;
    unsigned char operation_when_memory_full;
    unsigned char parallel_imaging;
    unsigned char trg_minimum_input_time;
    unsigned char encoder_minimum_input_time;
    unsigned char control_terminal_minimum_input_time;
    unsigned char brightness_output;
};

struct Program {
    //Trigger Settings
    unsigned char triggerMode;
    unsigned char samplingCycle;
    unsigned char batchMeasurement;
    unsigned short batchCount;
    unsigned char interTriggerPitch;
    unsigned long interTriggerPitchCount;
    unsigned char synchronization;
    unsigned char mutualInterferencePrevention;
    unsigned char mutualInterferencePreventionSlaveEmission;
    unsigned char encoderInputMode;
    unsigned char subSamplingOptions;
    unsigned short pointsToSubSample;
    // Imaging Settings
    unsigned char binning;
    unsigned char measurementRangeXDirection;
    unsigned short measurementRangeXDirectionCenter;
    unsigned char measurementRangeZDirection;
    unsigned short measurementRangeZDirectionCenter;
    unsigned short measurementRangeZDirectionBinning;
    unsigned char dynamicRange;
    unsigned char exposureTime;
    unsigned char exposureMode;
    unsigned char multiEmissionDetailsOptimizedLightIntensity;
    unsigned char multiEmissionSynthesis;
    unsigned char maskSettingsUpper1Enabled;
    unsigned char maskSettingsUpper2Enabled;
    unsigned char maskSettingsUpper3Enabled;
    unsigned char maskSettingsLower1Enabled;
    unsigned char maskSettingsLower2Enabled;
    unsigned char maskSettingsLower3Enabled;
    unsigned short maskSettingsUpper1XCoordinate1;
    unsigned short maskSettingsUpper2XCoordinate1;
    unsigned short maskSettingsUpper3XCoordinate1;
    unsigned short maskSettingsLower1XCoordinate1;
    unsigned short maskSettingsLower2XCoordinate1;
    unsigned short maskSettingsLower3XCoordinate1;
    unsigned short maskSettingsUpper1ZCoordinate1;
    unsigned short maskSettingsUpper2ZCoordinate1;
    unsigned short maskSettingsUpper3ZCoordinate1;
    unsigned short maskSettingsLower1ZCoordinate1;
    unsigned short maskSettingsLower2ZCoordinate1;
    unsigned short maskSettingsLower3ZCoordinate1;
    unsigned short maskSettingsUpper1XCoordinate2;
    unsigned short maskSettingsUpper2XCoordinate2;
    unsigned short maskSettingsUpper3XCoordinate2;
    unsigned short maskSettingsLower1XCoordinate2;
    unsigned short maskSettingsLower2XCoordinate2;
    unsigned short maskSettingsLower3XCoordinate2;
    unsigned short maskSettingsUpper1ZCoordinate2;
    unsigned short maskSettingsUpper2ZCoordinate2;
    unsigned short maskSettingsUpper3ZCoordinate2;
    unsigned short maskSettingsLower1ZCoordinate2;
    unsigned short maskSettingsLower2ZCoordinate2;
    unsigned short maskSettingsLower3ZCoordinate2;
    unsigned short maskSettingsUpper1XCoordinate3;
    unsigned short maskSettingsUpper2XCoordinate3;
    unsigned short maskSettingsUpper3XCoordinate3;
    unsigned short maskSettingsLower1XCoordinate3;
    unsigned short maskSettingsLower2XCoordinate3;
    unsigned short maskSettingsLower3XCoordinate3;
    unsigned short maskSettingsUpper1ZCoordinate3;
    unsigned short maskSettingsUpper2ZCoordinate3;
    unsigned short maskSettingsUpper3ZCoordinate3;
    unsigned short maskSettingsLower1ZCoordinate3;
    unsigned short maskSettingsLower2ZCoordinate3;
    unsigned short maskSettingsLower3ZCoordinate3;
    unsigned char lightIntensityControlMode;
    unsigned char lightIntensityUpperLimit;
    unsigned char lightIntensityLowerLimit;
    unsigned short lightIntensityControlTargetAreaStart;
    unsigned short lightIntensityControlTargetAreaStop;
    unsigned char peakDetectionSensitivity;
    unsigned char invalidDataInterpolationCount;
    unsigned char peakSelection;
    unsigned char peakWidthFilter;
    unsigned char peakWidthFilterStrength;
    unsigned char strayLightSuppressionFunction;
    unsigned char strayLightSuppressionFunctionFilterStrength;
    //Profile
    unsigned char subSamplingXAxis;
    unsigned char deadZoneDataInterpolation;
    unsigned char reverseX;
    unsigned char reverseZ;
    signed int shiftX;
    signed int shiftZ;
    unsigned char medianXAxis;
    unsigned char medianYAxis;
    unsigned char smoothing;
    unsigned char averagingCount;
    unsigned char invalidDataProcessingYProcessCount;
    unsigned char invalidDataProcessingYResumeCount;
    unsigned char tiltCorrectionOnOff;
    unsigned char tiltCorrectionLineCalculationAreaCount;
    signed int tiltCorrectionAreaStartPosition1;
    signed int tiltCorrectionAreaEndPosition1;
    signed int tiltCorrectionAreaStartPosition2;
    signed int tiltCorrectionAreaEndPosition2;
    signed short tiltCorrectionPostCorrectionAngle;
    signed short tiltCorrectionCorrectionAngle;
    unsigned char heightCorrectionOnOff;
    signed int heightCorrectionAreaStartPosition1;
    signed int heightCorrectionAreaEndPosition1;
    signed int heightCorrectionAreaStartPosition2;
    signed int heightCorrectionAreaEndPosition2;
    unsigned int heightCorrectionPostCorrectionHeight;
    unsigned int heightCorrectionSpan;
};
typedef struct LJX8IF_TARGET_SETTING {
    unsigned char byType = 0;
    unsigned char byCategory = 0;
    unsigned char byItem = 0;
    unsigned char reserve = 0;
    unsigned char byTarget1 = 0;
    unsigned char byTarget2 = 0;
    unsigned char byTarget3 = 0;
    unsigned char byTarget4 = 0;
    LJX8IF_TARGET_SETTING(unsigned char type, unsigned char category, unsigned char item ){
        byType = type;
        byCategory = category;
        byItem = item;
    }
    LJX8IF_TARGET_SETTING() {}
};
typedef struct {
    BYTE	abyIpAddress[4];	// The IP address of the controller to connect to.
    WORD	wPortNo;			// The port number of the controller to connect to.
    BYTE	reserve[2];			// Reserved
} LJX8IF_ETHERNET_CONFIG;

enum LJSensorType{
    LJ_X8020 = 0,
    LJ_X8080 = 1,
    LJ_X8200 = 2,
    LJ_X8400 = 3,
    LJ_X8900 = 4,
    LJ_V7020K = 5,
    LJ_V7020 = 6,
    LJ_V7060K = 7,
    LJ_V7060 = 8,
    LJ_V7080 = 9,
    LJ_V7200 = 10,
    LJ_V7300 = 11
};

enum Parameter {
    DeviceName,
    OperationAtNextPowerOn,
    HighSpeedCommunicationBandRestriction,
    MTUDuringHighSpeedCommunication,
    IPAddress,
    SubnetMask,
    Gateway,
    TCPCommandPortNumber,
    TCPHighSpeedPortNumber,
    MemoryAllocation,
    OperationWhenMemoryFull,
    ParallelImaging,
    TRGMinimumInputTime,
    ENCODERMinimumInputTime,
    ControlTerminalMinimumInputTime,
    BrightnessOutput,
    TriggerMode,
    SamplingCycle,
    BatchMeasurement,
    BatchCount,
    InterTriggerPitch,
    InterTriggerPitchCount,
    SynchronizatonOfMultipleControllers,
    MutualInterferencePrevention,
    InputMode,
    SubSampling,
    PointsToSubSample,
    Binning,
    MeasurementRangeXDirection,
    MeasurementRangeZDirection,
    DynamicRange,
    ExposureTime,
    ExposureMode,
    MultiEmissionDetailsOptimizedLightIntensity,
    MultiEmissionDetailsSynthesis,
    MaskSetting,
    LightIntensityControlMode,
    LightIntensityControlLowerLimitValue,
    LightIntensityControlUpperLimitValue,
    LightIntensityControlTargetArea,
    PeakDetectionSensitivity,
    InvalidDataInterpolationCount,
    PeakSelection,
    PeakWidthFilter,
    StrayLightSuppressionFunction,
    SubSamplingXAxis,
    DeadZoneDataInterpolation,
    ReverseX,
    ReverseZ,
    ShiftX,
    ShiftZ,
    MedianXAxis,
    MedianZAxis,
    Smoothing,
    Averaging,
    InvalidDataProcessingz,
    TiltCorrection,
    HeightCorection
};
enum OperationAtNextPowerOnOptions {
    OperationAtNextPowerOn_BOOTPThenIPAddressFixed = 0,
    OperationAtNextPowerOn_IPAddressFixed = 1,
    OperationAtNextPowerOn_BOOTP = 2
};
enum HighSpeedCommunicationBandRestrictionOptions {
    HighSpeedCommunicationBandRestriction_OFF = 0,
    HighSpeedCommunicationBandRestriction_500Mbps = 1,
    HighSpeedCommunicationBandRestriction_200Mbps = 2,
    HighSpeedCommunicationBandRestriction_100Mbps = 3
};
enum MemoryAllocationOptions {
    MemoryAllocation_DoubleBuffer = 0,
    MemoryAllocation_AllAreas = 1
};

enum OperationWhenMemoryFullOptions {
    OperationWhenMemoryFull_Overwrite = 0,
    OperationWhenMemoryFullStop = 1
};

enum ParallelImagingOptions {
    ParallelImaging_Disabled = 0,
    ParallelImaging_Enabled = 1
};

enum TRGMinimumInputTimeOptions {
    TRGMinimumInputTime_7us = 0,
    TRGMinimumInputTime_10us = 1,
    TRGMinimumInputTime_20us = 2,
    TRGMinimumInputTime_50us = 3,
    TRGMinimumInputTime_100us = 4,
    TRGMinimumInputTime_200us = 5,
    TRGMinimumInputTime_500us = 6,
    TRGMinimumInputTime_1ms = 7
};

enum ENCODERMinimumInputTimeOptions {
    ENCODERMinimumInputTime_120ns = 0,
    ENCODERMinimumInputTime_150ns = 1,
    ENCODERMinimumInputTime_250ns = 2,
    ENCODERMinimumInputTime_500ns = 3,
    ENCODERMinimumInputTime_1us = 4,
    ENCODERMinimumInputTime_2us = 5,
    ENCODERMinimumInputTime_5us = 6,
    ENCODERMinimumInputTime_10us = 7,
    ENCODERMinimumInputTime_20us = 8
};

enum ControlTerminalMinimumInputTimeOptions {
    ControlTerminalMinimumInputTime_250us = 0,
    ControlTerminalMinimumInputTime_1ms = 1
};

enum BrightnessOutputOptions {
    BrightnessOutput_HeightDataOnly = 0,
    BrightnessOutput_HeightAndBrightnessData = 1
};

enum TriggerModeOptions {
    TriggerMode_Continuous = 0,
    TriggerMode_External = 1,
    TriggerMode_Encoder = 2
};

enum SamplingCycleOptions {
    SamplingCycleLJX_10Hz = 0,
    SamplingCycleLJX_20Hz = 1,
    SamplingCycleLJX_50Hz = 2,
    SamplingCycleLJX_100Hz = 3,
    SamplingCycleLJX_200Hz = 4,
    SamplingCycleLJX_500Hz = 5,
    SamplingCycleLJX_1KHz = 6,
    SamplingCycleLJX_2KHz = 7,
    SamplingCycleLJX_4KHz = 8,
    SamplingCycleLJX_8KHz = 9,
    SamplingCycleLJX_16KHz = 10,
    SamplingCycleLJV_10Hz = 0,
    SamplingCycleLJV_20Hz = 1,
    SamplingCycleLJV_50Hz = 2,
    SamplingCycleLJV_100Hz = 3,
    SamplingCycleLJV_200Hz = 4,
    SamplingCycleLJV_500Hz = 5,
    SamplingCycleLJV_1KHz = 6,
    SamplingCycleLJV_2KHz = 7,
    SamplingCycleLJV_4KHz = 8,
    SamplingCycleLJV_4K13Hz = 9,
    SamplingCycleLJV_8KHz = 10,
    SamplingCycleLJV_16KHz = 11,
    SamplingCycleLJV_32KHz = 12,
    SamplingCycleLJV_64KHz = 13,
    SamplingCycleLJVB_10Hz = 0,
    SamplingCycleLJVB_20Hz = 1,
    SamplingCycleLJVB_50Hz = 2,
    SamplingCycleLJVB_100Hz = 3,
    SamplingCycleLJVB_200Hz = 4,
    SamplingCycleLJVB_500Hz = 5,
    SamplingCycleLJVB_1KHz = 6,
    SamplingCycleLJVB_2KHz = 7,
    SamplingCycleLJVB_4KHz = 8,
    SamplingCycleLJVB_4K13Hz = 9,
    SamplingCycleLJVB_8KHz = 10
};

enum BatchMeasurementOptions {
    BatchMeasurementBatch_OFF = 0,
    BatchMeasurementBatch_ON = 1
};

enum InterTriggerPitchOptions {
    InterTriggerPitch_OFF = 0,
    InterTriggerPitch_ON = 1
};

enum SynchronizationOfMultipleControllersOptions {
    SynchronizationOfMultipleControllers_OFF = 0,
    SynchronizationOfMultipleControllers_Master = 1,
    SynchronizationOfMultipleControllers_Slave = 2
};

enum MutualInterferencePreventionOptions {
    MutualInterferencePrevention_OFF = 0,
    MutualInterferencePrevention_ON = 1
};

enum MutualInterferencePreventionSlaveEmissionOptions {
    MutualInterferencePreventionSlaveEmission_SameAsMaster = 0,
    MutualInterferencePreventionSlaveEmission_AlterningWithTheMaster = 1
};

enum EncoderInputModeOptions {
    EncoderTriggerInputMode_1Phase1Time = 0,
    EncoderTriggerInputMode_2Phase1Time = 1,
    EncoderTriggerInputMode_2Phase2Times = 2,
    EncoderTriggerInputMode_2Phase4Times = 3
};

enum SubSamplingOptions {
    SubSampling_OFF = 0,
    SubSampling_ON = 1
};

enum BinningOptions {
    Binning_OFF = 0,
    Binning_ON = 1
};

enum MeasurementRangeXDirectionOptions {
    MeasurementRangeXDirectionLJX_FULL = 0,
    MeasurementRangeXDirectionLJX_ThreeQuarters = 1,
    MeasurementRangeXDirectionLJX_OneAndHalf = 2,
    MeasurementRangeXDirectionLJX_OneQuarter = 3,
    MeasurementRangeXDirectionLJV_FULL = 0,
    MeasurementRangeXDirectionLJV_MIDDLE = 1,
    MeasurementRangeXDirectionLJV_SMALL = 2
};

enum MeasurementRangeZDirectionOptions {
    MeasurementRangeZDirectionLJX_FULL = 0,
    MeasurementRangeZDirectionLJX_OneAndHalf = 1,
    MeasurementRangeZDirectionLJX_OneQuarter = 2,
    MeasurementRangeZDirectionLJX_OneEighth = 3,
    MeasurementRangeZDirectionLJX_OneSixteenth = 4,
    MeasurementRangeZDirectionLJX_OneThirtyTwo = 5,
    MeasurementRangeZDirectionLJV_FULL = 0,
    MeasurementRangeZDirectionLJV_MIDDLE = 1,
    MeasurementRangeZDirectionLJV_SMALL = 2
};

enum MeasurementRangeZDirectionBinningOptions {
    MeasurementRangeZDirectionBinning_OFF = 1,
    MeasurementRangeZDirectionBinning_ON = 0
};

enum ExposureTimeOptions {
    ExposureTimeLJX_15us = 0,
    ExposureTimeLJX_30us = 1,
    ExposureTimeLJX_60us = 2,
    ExposureTimeLJX_120us = 3,
    ExposureTimeLJX_240us = 4,
    ExposureTimeLJX_480us = 5,
    ExposureTimeLJX_960us = 6,
    ExposureTimeLJX_1700us = 7,
    ExposureTimeLJX_4ms8 = 8,
    ExposureTimeLJX_9ms6 = 9,
    ExposureTimeLJV_15us = 0,
    ExposureTimeLJV_30us = 1,
    ExposureTimeLJV_60us = 2,
    ExposureTimeLJV_120us = 3,
    ExposureTimeLJV_240us = 4,
    ExposureTimeLJV_480us = 5,
    ExposureTimeLJV_960us = 6,
    ExposureTimeLJV_1920us = 7,
    ExposureTimeLJV_5ms = 8,
    ExposureTimeLJV_10ms = 9
};

enum ExposureModeOptions {
    ExposureMode_Standard = 0,
    ExposureMode_MultiEmissionSynthesis = 1,
    ExposureMode_MultiEmissionOptimizedLightIntensity = 2
};

enum MultiEmissionDetailsOptimizedLightIntensityOptions {
    MultiEmissionDetailsOptimizedLightIntensity_Two = 0,
    MultiEmissionDetailsOptimizedLightIntensity_Four = 1
};

enum MultiEmissionDetailsSynthesisOptions {
    MultiEmissionDetailsSynthesis_Three = 0,
    MultiEmissionDetailsSynthesis_Five = 1
};

enum MaskSettingOptions {
    Mask_Disabled = 0,
    Mask_Rectangle = 1,
    Mask_Triangle = 2
};

enum LightIntensityControlModeOptions {
    LightIntensityControlMode_AUTO = 0,
    LightIntensityControlMode_MANUAL = 1
};

enum PeakSelectionOptions {
    PeakSelectionLJX_Standard = 0,
    PeakSelectionLJX_NEAR = 1,
    PeakSelectionLJX_FAR = 2,
    PeakSelectionLJX_INVALID = 3,
    PeakSelectionLJV_Standard = 0,
    PeakSelectionLJV_NEAR = 1,
    PeakSelectionLJV_FAR = 2,
    PeakSelectionLJV_RemoveXMultiReflection = 3,
    PeakSelectionLJV_RemoveYMultiReflection = 4,
    PeakSelectionLJV_INVALID = 5
};

enum PeakWidthFilterOptions {
    PeakWidthFilter_OFF = 0,
    PeakWidthFilter_ON = 1
};

enum StrayLightSuppressionFunctionOptions {
    StrayLightSuppressionFunction_OFF = 0,
    StrayLightSuppressionFunction_ON = 1
};

enum SubSamplingXAxisOptions {
    SubSamplingXAxis_OFF = 0,
    SubSamplingXAxis_OneAndHalf = 1,
    SubSamplingXAxis_OneQuarter = 2
};

enum DeadZoneDataInterpolationOptions {
    DeadZoneDataInterpolation_NoInterpolation = 0,
    DeadZoneDataInterpolation_LinearInterpolation = 1,
    DeadZoneDataInterpolation_VerticalInterpolation = 2
};

enum ReverseXOptions {
    ReverseX_OFF = 0,
    ReverseX_ON = 1
};

enum ReverseZOptions {
    ReverseZ_OFF = 0,
    ReverseZ_ON = 1
};

enum MedianXAxisOptions {
    MedianXAxis_OFF = 0,
    MedianXAxis_3 = 1,
    MedianXAxis_5 = 2,
    MedianXAxis_7 = 3,
    MedianXAxis_9 = 4,
    MedianXAxis_17 = 5,
    MedianXAxis_25 = 6,
    MedianXAxis_33 = 7
};

enum MedianYAxisOptions {
    MedianYAxis_OFF = 0,
    MedianYAxis_3 = 1,
    MedianYAxis_5 = 2,
    MedianYAxis_7 = 3,
    MedianYAxis_9 = 4,
};

enum SmoothingCountOptions {
    SmoothingCount_1 = 0,
    SmoothingCount_2 = 1,
    SmoothingCount_4 = 2,
    SmoothingCount_8 = 3,
    SmoothingCount_16 = 4,
    SmoothingCount_32 = 5,
    SmoothingCount_64 = 6
};
enum SmoothingRetentionOptions {
    SmoothingRetention_OFF = 0,
    SmoothingRetention_ON = 1
};

enum AveragingOptions {
    Averaging_1 = 0,
    Averaging_2 = 1,
    Averaging_4 = 2,
    Averaging_8 = 3,
    Averaging_16 = 4,
    Averaging_32 = 5,
    Averaging_64 = 6,
    Averaging_128 = 7,
    Averaging_256 = 8,
};

enum TiltCorrectionOptions {
    TiltCorrection_OFF = 0,
    TiltCorrection_ON = 1
};

enum HeightCorectionOptions {
    HeightCorrection_OFF = 0,
    HeightCorrection_ON = 1
};
struct EnviromentSettings {
    char device_name[32];
    unsigned char operation_at_next_power_on;
    unsigned char high_speed_communication_band_restriction;
    unsigned short mtu_during_high_speed_communication;
    unsigned char ip_address[4];
    unsigned char subnet_mask[4];
    unsigned char gateway[4];
    unsigned short tcp_command_port;
    unsigned short tcp_highspeed_port;
};

typedef struct FibreLJXSettings {
    char format_identifier[19] = {'f', 'i', 'b', 'r', 'e', 'L', 'J', 'X', 'S', 'e', 't', 't','i','n','g','s', '1', '.', '0'};
    char sensorSN[16];
    char controllerSN[16];
    int active_program;
    LJSensorType sensor;
    EnviromentSettings enviroment;
    CommonSettings common;
    Program programs[16];
};
#endif // LJSETTINGS_STRUCTS_H
