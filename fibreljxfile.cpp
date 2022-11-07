#include "fibreljxfile.h"
#include <QByteArray>
#include <QFile>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <opencv2/opencv.hpp>
struct fibreLJXHeader{
    char format_identifier[11] = {'f', 'i', 'b', 'r', 'e', 'L', 'J', 'X', '1', '.', '0'};
    unsigned long long settings_start = 0;
    unsigned long long settings_length = 0;
    unsigned long long height_matrix_start = 0;
    unsigned long long height_matrix_length = 0;
    unsigned long long intensity_matrix_start = 0;
    unsigned long long intensity_matrix_length = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    int sensor_type = 0;
    char sensor_sn[16];
    char controller_sn[16];
};

FibreLJXFile::FibreLJXFile()
{
}

void FibreLJXFile::read(const std::string &path, LJSensorType sensor)
{
    std::string file_extension(path.substr(path.rfind(".") + 1));
    if(file_extension == "csv") {
        readCsv(path);
        m_sensor_version = sensor;
    } else if (file_extension == "fibreljx") {
        std::cout << "readFibreLJX" << std::endl;
        readFibreLJX(path);
        std::cout << "readFibreLJX done" << std::endl;
    } else {
        throw std::invalid_argument("The file path must end with .fibreljx. For backward compatibility reasons .csv files will also work.");
    }
}
void FibreLJXFile::write(const std::string &filename)
{
    QByteArray settings = m_settings.getData();
    QByteArray height = compressedHeight();
    QByteArray intensity = compressedIntensity();

    fibreLJXHeader header;
    header.width = m_height_raw.cols;
    header.height = m_height_raw.rows;
    header.settings_start = sizeof(fibreLJXHeader);
    header.settings_length = settings.size();
    header.height_matrix_start = header.settings_start + settings.size();
    header.height_matrix_length = height.size();
    for(int i = 0; i < 16; i++) {
        header.sensor_sn[i] = m_sensor_sn[i];
        header.controller_sn[i] = m_controller_sn[i];
    }

    if(m_intensity_raw.rows > 0) {
        header.intensity_matrix_start = header.height_matrix_start + header.height_matrix_length;
        header.intensity_matrix_length = intensity.size();
    }


    QFile file(QString::fromStdString(filename));
    file.open(QIODevice::WriteOnly);
    file.write(QByteArray((char*) &header, sizeof(fibreLJXHeader)));
    file.write(settings);
    file.write(height);
    file.write(intensity);
    file.close();
}

cv::Mat FibreLJXFile::height()
{
    return m_height_raw;
}

void FibreLJXFile::setHeight(cv::Mat &h)
{
    if(h.type() != CV_32S)
        throw std::invalid_argument("type != CV_32S");
    m_height_raw = h;
}

cv::Mat FibreLJXFile::intensity()
{
    return m_intensity_raw;
}

void FibreLJXFile::setIntensity(cv::Mat &i)
{
    if(i.type() != CV_16U)
        throw std::invalid_argument("type != CV_16U");
    m_intensity_raw = i;
    m_with_intensity = true;
}

LJSettings FibreLJXFile::settings()
{
    return m_settings;
}

void FibreLJXFile::setSettings(LJSettings &s)
{
    m_settings = s;
}

LJSensorType FibreLJXFile::sensor()
{
    return m_sensor_version;
}

void FibreLJXFile::setSensor(LJSensorType &s)
{
    m_sensor_version = s;
}

void FibreLJXFile::readCsv(std::string path)
{
    std::ifstream file;
    file.open(path);
    std::vector<int> values;
    if (file.is_open()) {
        std::cout << "is open" << std::endl;
        std::string line;
        std::string delim = ",";
        bool firstline = true;
        int elementsPerLine = 1;
        while (std::getline(file, line)) {
            auto start = 0U;
            auto end = line.find(delim);
            while (end != std::string::npos)
            {
                if(firstline)
                    elementsPerLine++;
                values.push_back(stoi(line.substr(start, end - start)));
                start = end + delim.length();
                end = line.find(delim, start);
            }
            firstline = false;
            values.push_back(stoi(line.substr(start, end)));

        }
        int rowCount = (int)values.size() / elementsPerLine;
        cv::Mat inFile = cv::Mat(values).reshape(1,rowCount);
        cv::Mat height = inFile.colRange(0,3200);

        m_height_raw = height.clone();
        if(elementsPerLine > 3200) {
            cv::Mat intensity = inFile.colRange(3200, 6400);
            m_intensity_raw = intensity.clone();
            m_with_intensity = true;
            m_intensity_raw.convertTo(m_intensity_raw,CV_16UC1);
        }
        file.close();
    }
    else {
        std::cout << "not open" << std::endl;
    }
}
void FibreLJXFile::readFibreLJX(const std::string &filename)
{
    fibreLJXHeader header;
    LJSettings settings;
    cv::Mat height;
    cv::Mat intensity;

    QFile file(QString::fromStdString(filename));
    file.open(QIODevice::ReadOnly);
    QByteArray inData = file.readAll();
    QDataStream ds(inData);
    std::cout << "data" << std::endl;

    unsigned long long pos = 0;
    unsigned long long max_pos = 0;
    while(pos <= max_pos) {
        QByteArray s;
        if(pos == 0) {
            pos += sizeof(fibreLJXHeader);
            ds.readRawData((char*) &header, sizeof(fibreLJXHeader));
            std::cout << "got header" << std::endl;
            if(max_pos < header.settings_start)
                max_pos = header.settings_start;
            if(max_pos < header.height_matrix_start)
                max_pos = header.height_matrix_start;
            if(max_pos < header.intensity_matrix_start)
                max_pos = header.intensity_matrix_start;
            std::cout << "max_pos " << max_pos << std::endl;
            std::cout << "Intensity matrix length " <<  header.intensity_matrix_length << std::endl;
        } else if(pos == header.settings_start) {
            std::cout << "got settings" << std::endl;
            pos += header.settings_length;
            s.fill(0, header.settings_length);
            ds.readRawData(s.data(), sizeof(FibreLJXSettings));
            std::cout << "got settings" << std::endl;
            settings.setData(s);
            std::cout << "got settings" << std::endl;
        } else if(pos == header.height_matrix_start) {
            std::cout << "got height" << std::endl;
            pos += header.height_matrix_length;
            s.fill(0, header.height_matrix_length);
            height = cv::Mat(header.height, header.width, CV_32S);
            ds.readRawData(s.data(), header.height_matrix_length);
            s = qUncompress(s);
            std::memcpy(height.data, s.constData(), CV_ELEM_SIZE(height.type())*height.total());
        } else if(pos == header.intensity_matrix_start) {
            std::cout << "got intensity" << std::endl;
            pos += header.intensity_matrix_length;
            s.fill(0, header.intensity_matrix_length);
            intensity = cv::Mat(header.height, header.width, CV_16U);
            ds.readRawData(s.data(), header.intensity_matrix_length);
            s = qUncompress(s);
            std::memcpy(intensity.data, s.constData(), CV_ELEM_SIZE(intensity.type())*intensity.total());
        } else {
            ds.skipRawData(1);
            pos += 1;
        }

    }

    std::cout << "data dane" << std::endl;
    m_sensor_version = (LJSensorType) header.sensor_type;
    m_settings = settings;
    m_intensity_raw = intensity;
    m_height_raw = height;
}
QByteArray FibreLJXFile::compressMat(cv::Mat &data, int compressionLevel)
{
    return qCompress(QByteArray((char*)data.data, CV_ELEM_SIZE(data.type()) * data.total()), compressionLevel);
}
QByteArray FibreLJXFile::compressedHeight()
{
    return compressMat(m_height_raw);
}
QByteArray FibreLJXFile::compressedIntensity()
{
    return m_with_intensity ? compressMat(m_intensity_raw) : QByteArray();
}
