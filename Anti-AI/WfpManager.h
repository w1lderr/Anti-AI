#pragma once

#include <windows.h>
#include <string>

bool SetupWFPLayers(HANDLE engine);
bool AddIPv4Filter(HANDLE engine, UINT32 ip, const std::string& label);