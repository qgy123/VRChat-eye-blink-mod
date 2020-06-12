#include <cstdio>
#include <cstdlib>
#include <thread>
#include "SRanipal.h"
#include "SRanipal_Eye.h"
#include "SRanipal_Enums.h"
#include "debug.h"
#include <windows.h>
#include <fmt/core.h>
#include <iomanip>
#pragma comment (lib, "SRanipal.lib")

bool is_blink = false;

std::thread* t = nullptr;
bool enable_eye = false;
bool looping = false;

bool GetValidity(UINT64 eye_data_validata_bit_mask)
{
	return (eye_data_validata_bit_mask & 1 << (int)ViveSR::anipal::Eye::SINGLE_EYE_DATA_GAZE_ORIGIN_VALIDITY) > 0;
}

void streaming() {
	ViveSR::anipal::Eye::EyeData eye_data{};

	while (looping) {
		if (enable_eye) {
			int result = ViveSR::anipal::Eye::GetEyeData(&eye_data);
			if (result == ViveSR::Error::WORK) {
				//float* gaze = eye_data.verbose_data.left.gaze_direction_normalized.elem_;
				
				float left_openness = eye_data.verbose_data.left.eye_openness;
				float right_openness = eye_data.verbose_data.right.eye_openness;
				
				/*if (gaze[0] || gaze[1] || gaze[2])
					debug_out(L"[Eye] Gaze: %.2f %.2f %.2f\n", gaze[0], gaze[1], gaze[2]);*/
				
				if (GetValidity(eye_data.verbose_data.left.eye_data_validata_bit_mask) || GetValidity(eye_data.verbose_data.right.eye_data_validata_bit_mask))
				{
					if (left_openness < 0.1 || right_openness < 0.1)
					{
						is_blink = true;
						std::this_thread::sleep_for(std::chrono::milliseconds(200));
						//DEBUG_OUT(fmt::format(L"[Eye] Blink! openness: {0} {1}\n", left_openness, right_openness));
					}
					else { is_blink = false; }
				}
				
			}
		}
		Sleep(0);
	}
}

bool Initialize_Eye_Tracker()
{
	if (!ViveSR::anipal::Eye::IsViveProEye()) {
		DEBUG_OUT(L"This device does not have eye-tracker, please change your HMD\n");
		return FALSE;
	}

	int error = ViveSR::anipal::Initial(ViveSR::anipal::Eye::ANIPAL_TYPE_EYE, NULL);

	if (error == ViveSR::Error::WORK)
	{
		enable_eye = true; DEBUG_OUT(L"Successfully initialize Eye engine.\n");
		return TRUE;
	}
	else if (error == ViveSR::Error::RUNTIME_NOT_FOUND)
		DEBUG_OUT(L"please follows SRanipal SDK guide to install SR_Runtime first\n");
	else
		DEBUG_OUT(fmt::format(L"Fail to initialize Eye engine. please refer the code {} of ViveSR::Error.\n", error));

	return FALSE;
}

void Start_Tracking_Thread()
{
	if (t == nullptr) {
		t = new std::thread(streaming);
		if (t)   looping = true;
	}
}

void Stop_Tracking_Thread()
{
	looping = false;
	if (t == nullptr) return;
	t->join();
	delete t;
	t = nullptr;
}

void Release_Eye_tracker()
{
	int error = ViveSR::anipal::Release(ViveSR::anipal::Eye::ANIPAL_TYPE_EYE);
	DEBUG_OUT(L"Successfully release all anipal engines.\n");
	enable_eye = false;
}