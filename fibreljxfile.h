#ifndef FIBRELJXFILE_H
#define FIBRELJXFILE_H

#include "FibreLJXFile_global.h"
#include <string>
#include <opencv2/imgcodecs.hpp>
#include "ljsettings.h"
#include <QByteArray>
class FIBRELJXFILE_EXPORT FibreLJXFile
{
public:
    FibreLJXFile();
    // Einlesen einer gespeicherten Lasertriangulationsdatei
    // @param filename: Dateiname mit Endung .fibreljx oder .csv.
    // @param sensor: Dieser Parameter wird nur bei .csv-Dateien verwendet.
    void read(const std::string& filename, LJSensorType sensor = LJSensorType::LJ_X8200);
    // Schreiben einer Lasertriangulationsdatei im FibreLJXFile-Format.
    // @param filename: Beliebiger Dateiname.
    //                  Dieser sollte auf .fibreljx enden, da ansonsten die Datei vor dem erneuten einlesen umbeannt werden muss.
    //                  Bestehende Daten werden überschrieben.
    void write(const std::string& filename);
    // Höhendatenmatrix Format: CV_32S
    //   Zitat Doku: The profile data is stored in units of 0.01 μm.
    //               Example: If the value is 1.98750 mm, it is stored as 198750.
    //               -2147483648 (0x80000000) und -2147483647 (0x80000001) Invalid Data => This value is output when the data is located in a dead zone.
    //               -2147483646 (0x80000002) Dead zone data => This value is output when the light intensity reflected from the target cannot be detected and when the data is invalid due to a setting such as a mask having been set.
    //               -2147483645 (0x80000003) Judgment standby data => This value is output when there is an insufficient amount of profiles for averaging
    cv::Mat height();
    // Grauwertdatenmatrix Format: CV_16U
    // Zitat Doku: A value from 0 to 1023 is stored for the brightness data.
    cv::Mat intensity();
    // Messeinstellungen bei der Highspeedaufzeichnung => Siehe auch LJSettings-Klasse
    LJSettings settings();
    LJSensorType sensor();

    //Ab hier sollte es für dich nicht mehr relevant sein.
    void setHeight(cv::Mat &h);
    void setIntensity(cv::Mat &i);
    void setSettings(LJSettings &s);
    void setSensor(LJSensorType &s);

private:
    cv::Mat m_height_raw; // CV_32S
    cv::Mat m_intensity_raw; // CV_16U
    LJSensorType m_sensor_version = LJSensorType::LJ_X8200;
    LJSettings m_settings;
    char m_sensor_sn[16];
    char m_controller_sn[16];
    bool m_with_intensity = false;

    void readCsv(std::string path);
    void readFibreLJX(const std::string& filename);
    QByteArray compressMat(cv::Mat &data, int compressionLevel = -1);
    QByteArray compressedHeight();
    QByteArray compressedIntensity();

};
#endif // FIBRELJXFILE_H
