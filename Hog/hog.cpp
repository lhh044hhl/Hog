#include<opencv.hpp>
using namespace std;
using namespace cv;

void Hog(Mat refMat,float *ref_hist) {
	double pi = 3.1415926;
	Mat gx, gy;
	Mat mag, angle;
	Sobel(refMat, gx, CV_32F, 1, 0, 1);
	Sobel(refMat, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, false);

	int cellsize = 16;
	int nX = refMat.cols / cellsize;
	int nY = refMat.rows / cellsize;

	int bins = 8;
      ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float)*bins);
	int binsnum = 0;
	for (int n = 0;n < nX;n++) {
		for (int m = 0;m < nY;m++) {
			for (int n2 = n*16;n2 < n * 16+16;n2++) {
				for (int m2 = m*16;m2 < m * 16+ 16;m2++) {

					int angle_lh = angle.at<float>(n2, m2)/45;
					float mag_l = mag.at<float>(n2, m2);
					ref_hist[angle_lh + binsnum*8] += mag_l;

				}
			}
			binsnum++;
		}
	}
	delete[] ref_hist;

}

int main() {
	float sum1 = 0;
	float sum2 = 0;
	int bins = 8;
	float  *hist1 = new float[bins];
	memset(hist1, 0, sizeof(float)*bins);
	int length = sizeof(hist1) / sizeof(hist1[0]);
	float  *hist2 = new float[bins];
	memset(hist2, 0, sizeof(float)*bins);
	float  *hist3 = new float[bins];
	memset(hist3, 0, sizeof(float)*bins);

	Mat src1=imread("E:\\dignal picture\\hogTemplate.jpg");
	Mat src2 = imread("E:\\dignal picture\\img1.jpg");
	Mat src3 = imread("E:\\dignal picture\\img2.jpg");
	Hog(src1, hist1);
	Hog(src2, hist2);
	Hog(src3, hist3);
	float compare1, compare2;
	for (int n = 0;n < length;n++) {
	
		sum1 += (hist1[n] - hist2[n]) *(hist1[n] - hist2[n]);
	}
	for (int m = 0;m < length;m++) {

		sum2 += (hist1[m] - hist2[m]) *(hist1[m] - hist2[m]);
	}
	if (sum1 > sum2) {

		cout << "img2与原图更接近" << endl;

	}
	else {
		cout << "img1与原图更接近" << endl;
	}
	imshow("src1",src1);
	waitKey(0);
	delete[] hist1;
	delete[] hist2;
	delete[] hist3;
}