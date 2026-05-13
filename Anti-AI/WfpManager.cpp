#define WIN32_LEAN_AND_MEAN
#include "WfpManager.h"
#include "Config.h"

#include <winsock2.h>
#include <fwpmu.h>

using namespace std;

bool SetupWFPLayers(HANDLE engine)
{
    // Define custom provider grouping together the security rules 
    FWPM_PROVIDER0 provider = {};
    provider.providerKey = PROVIDER_GUID;
    provider.displayData.name = const_cast<wchar_t*>(L"AI Blocker Provider");
    DWORD r = FwpmProviderAdd0(engine, &provider, NULL);
    if (r != ERROR_SUCCESS && r != FWP_E_ALREADY_EXISTS) return false;

    // Define priority layer for network inspection and actions
    FWPM_SUBLAYER0 sublayer = {};
    sublayer.subLayerKey = SUBLAYER_GUID;
    sublayer.displayData.name = const_cast<wchar_t*>(L"AI Blocker Sublayer");
    sublayer.providerKey = const_cast<GUID*>(&PROVIDER_GUID);
    sublayer.weight = 0x0100;
    r = FwpmSubLayerAdd0(engine, &sublayer, NULL);

    return (r == ERROR_SUCCESS || r == FWP_E_ALREADY_EXISTS);
}

bool AddIPv4Filter(HANDLE engine, UINT32 ip, const string& label)
{
    wstring wlabel(label.begin(), label.end());

    FWPM_FILTER0 filter = {};
    filter.displayData.name = const_cast<wchar_t*>(wlabel.c_str());
    filter.providerKey = const_cast<GUID*>(&PROVIDER_GUID);
    filter.subLayerKey = SUBLAYER_GUID;

    // Check constraints upon network connection establishment creation
    filter.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V4;
    filter.action.type = FWP_ACTION_BLOCK;
    filter.weight.type = FWP_UINT8;
    filter.weight.uint8 = 15;

    // Add match configuration for rejecting outbound connection to resolved IP limits
    FWPM_FILTER_CONDITION0 cond = {};
    cond.fieldKey = FWPM_CONDITION_IP_REMOTE_ADDRESS;
    cond.matchType = FWP_MATCH_EQUAL;
    cond.conditionValue.type = FWP_UINT32;
    cond.conditionValue.uint32 = ntohl(ip);

    filter.numFilterConditions = 1;
    filter.filterCondition = &cond;

    return FwpmFilterAdd0(engine, &filter, NULL, NULL) == ERROR_SUCCESS;
}