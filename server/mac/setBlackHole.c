#include <CoreAudio/CoreAudio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stdio.h>

AudioObjectID findBlackHoleDevice() {
    AudioObjectID deviceID = kAudioObjectUnknown;
    UInt32 dataSize = 0;
    OSStatus status;

    // Get the number of devices
    status = AudioObjectGetPropertyDataSize(kAudioObjectSystemObject,
        &(AudioObjectPropertyAddress){kAudioHardwarePropertyDevices, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster},
        0, NULL, &dataSize);

    if (status != noErr) {
        printf("Error getting device data size: %d\n", status);
        return kAudioObjectUnknown;
    }

    UInt32 deviceCount = dataSize / sizeof(AudioObjectID);
    AudioObjectID *devices = (AudioObjectID *)malloc(dataSize);

    // Get the list of all devices
    status = AudioObjectGetPropertyData(kAudioObjectSystemObject,
        &(AudioObjectPropertyAddress){kAudioHardwarePropertyDevices, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster},
        0, NULL, &dataSize, devices);

    if (status != noErr) {
        printf("Error getting device data: %d\n", status);
        free(devices);
        return kAudioObjectUnknown;
    }

    // Loop through devices and find BlackHole
    for (UInt32 i = 0; i < deviceCount; i++) {
        AudioObjectID device = devices[i];
        CFStringRef deviceName;
        UInt32 size = sizeof(CFStringRef);

        // Get the device name
        status = AudioObjectGetPropertyData(device,
            &(AudioObjectPropertyAddress){kAudioDevicePropertyDeviceNameCFString, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster},
            0, NULL, &size, &deviceName);

        if (status == noErr && deviceName) {
            // Compare the device name with "BlackHole 2ch"
            if (CFStringCompare(deviceName, CFSTR("BlackHole 2ch"), 0) == kCFCompareEqualTo) {
                printf("Found BlackHole 2ch device\n");
                CFRelease(deviceName);
                free(devices);
                return device;
            }
            CFRelease(deviceName);
        }
    }

    free(devices);
    return kAudioObjectUnknown;
}

OSStatus setDefaultOutputDevice(AudioObjectID deviceID) {
    if (deviceID == kAudioObjectUnknown) {
        return -1;  // Invalid device ID
    }

    AudioObjectPropertyAddress address = {kAudioHardwarePropertyDefaultOutputDevice, kAudioObjectPropertyScopeGlobal, kAudioObjectPropertyElementMaster};
    return AudioObjectSetPropertyData(kAudioObjectSystemObject, &address, 0, NULL, sizeof(AudioObjectID), &deviceID);
}

int main() {
    AudioObjectID blackHoleDevice = findBlackHoleDevice();
    if (blackHoleDevice == kAudioObjectUnknown) {
        printf("BlackHole 2ch not found\n");
        return -1;
    }

    OSStatus status = setDefaultOutputDevice(blackHoleDevice);
    if (status == noErr) {
        printf("Successfully set BlackHole 2ch as default output\n");
    } else {
        printf("Error setting default output device: %d\n", status);
    }

    return 0;
}

