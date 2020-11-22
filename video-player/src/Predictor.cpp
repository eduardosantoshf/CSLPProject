#include<iostream>
#include<opencv2/opencv.hpp>
#include "Golomb2.cpp"

using namespace std;

class Predictor {
    private:
        int m;
        int predictorType;
        int framesNumber;
        int height;
        int width;
        bool flag = 1;
        string videoFormat;
        Golomb *golomb;
        WBitStream *wbs;
    
    public:
        Predictor(int predictorType, int m, string filename, int videoFormat, int framesNumber, int codingType) {
            if (codingType == 1) {
                this->predictorType = predictorType;
                this->m = m;
                this->videoFormat = videoFormat;
                this->framesNumber = framesNumber;

                golomb = new Golomb(filename, m, 1);
                
                wbs = new WBitStream(filename);
                wbs->writeNBits(videoFormat, 8);
                wbs->writeNBits(predictorType, 8);
                wbs->writeNBits(m, 8);
            }
            else {
                RBitStream rbs(filename);
                this->videoFormat = rbs.readNBits(8);
                cout << "Video format: " << this->videoFormat << endl;

                this->predictorType = rbs.readNBits(8);
                cout << "Predictor type: " << this->predictorType << endl;

                this->m = rbs.readNBits(8);
                cout << "Value of m used: " << this->m << endl;

                this->height = stoi(rbs.readString(4));
                cout << "Height: " << this->height << endl;

                this->width = stoi(rbs.readString(4));
                cout << "Width: " << this->width << endl;

                this->framesNumber = stoi(rbs.readString(4));
                cout << "Number of frames: " << this->framesNumber << endl;

                rbs.close();

                golomb = new Golomb(filename, m, 0);
                golomb->SkipNBytes(15);
            }
            
        }

        void encodeJPEG1(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int a = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((c - 1) >= 0)
                        a = (int) frame.at<uchar>(l, c - 1)
                    else
                        a = 0;

                    pixel = (int) frame.at<uchar>(l, c);

                    golomb->encode(pixel - a);
                }
            }
        }

        void encodeJPEG2(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int b = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((l - 1) >= 0)
                        b = (int) frame.at<uchar>(l - 1, c);
                    else
                        b = 0;

                    pixel = (int) frame.at<uchar>(l, c);
                    
                    golomb->encode(pixel - b);
                }
            }
        }

        void encodeJPEG3(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int c = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((l - 1) >= 0 && (c - 1) >= 0)
                        c = (int) frame.at<uchar>(l - 1, c - 1);
                    else
                        c = 0;
                    
                    pixel = (int) frame.at<uchar>(l, c);
                    
                    golomb->encode(pixel - c);
                }
            }
        }

        void encodeJPEG4(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int a = 0;
            int b = 0;
            int c2 = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((c - 1) >= 0)
                        a = (int) frame.at<uchar>(l, c - 1);
                    else
                        a = 0;
                    
                    if ((l - 1) >= 0)
                        b = (int) frame.at<uchar>(l - 1, c);
                    else
                        b = 0;
                    
                    if ((l - 1) >= 0 && (c - 1) >= 0)
                        c2 = (int) frame.at<uchar>(l - 1, c - 1);
                    else
                        c2 = 0;
                    
                    pixel = (int) frame.at<uchar>(l, c);

                    golomb->encode(pixel - (a + b - c2));
                }
            }
        }

        void encodeJPEG5(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int a = 0;
            int b = 0;
            int c2 = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((c - 1) >= 0)
                        a = (int) frame.at<uchar>(l, c - 1);
                    else
                        a = 0;
                    
                    if ((l - 1) >= 0)
                        b = (int) frame.at<uchar>(l - 1, c);
                    else
                        b = 0;
                    
                    if ((l - 1) >= 0 && (c - 1) >= 0)
                        c2 = (int) frame.at<uchar>(l - 1, c - 1);
                    else
                        c2 = 0;
                    
                    pixel = (int) frame.at<uchar>(l, c);

                    golomb->encode(pixel - (a + ((b - c2) / 2)));
                }
            }
        }

        void encodeJPEG6(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int a = 0;
            int b = 0;
            int c2 = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((c - 1) >= 0)
                        a = (int) frame.at<uchar>(l, c - 1);
                    else
                        a = 0;
                    
                    if ((l - 1) >= 0)
                        b = (int) frame.at<uchar>(l - 1, c);
                    else
                        b = 0;
                    
                    if ((l - 1) >= 0 && (c - 1) >= 0)
                        c2 = (int) frame.at<uchar>(l - 1, c - 1);
                    else
                        c2 = 0;
                    
                    pixel = (int) frame.at<uchar>(l, c);

                    golomb->encode(pixel - (b + ((a - c2) / 2)));
                }
            }
        }

        void encodeJPEG7(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int a = 0;
            int b = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((c - 1) >= 0)
                        a = (int) frame.at<uchar>(l, c - 1);
                    else
                        a = 0;
                    
                    if ((l - 1) >= 0)
                        b = (int) frame.at<uchar>(l - 1, c);
                    else
                        b = 0;

                    pixel = (int) frame.at<uchar>(l, c);

                    golomb->encode(pixel - ((a + b) / 2));
                }
            }
        }

        void encodeJPEGLS(Mat frame) {
            int lines = f.rows;
            int columns = f.cols;

            writeFrameSize(lines, columns, frame);

            int pixel;
            int a = 0;
            int b = 0;
            int c2 = 0;

            for (int l = 0; l < lines; l++) {
                for (int c = 0; c < columns; c++) {
                    if ((c - 1) >= 0)
                        a = (int) frame.at<uchar>(l, c - 1);
                    else
                        a = 0;
                    
                    if ((l - 1) >= 0)
                        b = (int) frame.at<uchar>(l - 1, c);
                    else
                        b = 0;
                    
                    if ((l - 1) >= 0 && (c - 1) >= 0)
                        c2 = (int) frame.at<uchar>(l - 1, c - 1);
                    else
                        c2 = 0;
                    
                    pixel = (int) frame.at<uchar>(l, c);

                    if (c2 >= max(a, b))
                        golomb->encode(pixel - min(a, b));
                    else if (c2 <= min(a, b))
                        golomb->encode(pixel - max(a, b));
                    else
                        golomb->encode(pixel - (a + b - c2));
                }
            }
        }

        void writeFrameSize(int lines, int columns, Mat frame) {
            if (flag) {
                string width  = to_string(columns);
                string height = to_string(lines);
                string frames = to_string(framesNumber);

                for (int w = 0; w < 4 - width.length(); w++){
                    width = "0" + width;
                }
                for (int h = 0; h < 4 - height.length(); h++){
                    height = "0" + height;
                }
                for (int f = 0; f < 4 - frames.length(); f++){
                    frames = "0" + frames;
                }

                wbs->writeString(width);
                wbs->writeString(height);
                wbs->writeString(frames);

                flag = 0;
            }
        }
};