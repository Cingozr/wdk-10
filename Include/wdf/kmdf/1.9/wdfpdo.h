/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

_WdfVersionBuild_

Module Name:

    WdfPdo.h

Abstract:

    This is the interface to the PDO WDFDEVICE handle.

Environment:

    kernel mode only

Revision History:

--*/

#ifndef _WDFPDO_1_9_H_
#define _WDFPDO_1_9_H_



#if (NTDDI_VERSION >= NTDDI_WIN2K)



typedef
_Function_class_(EVT_WDF_DEVICE_RESOURCES_QUERY)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_DEVICE_RESOURCES_QUERY(
    _In_
    WDFDEVICE Device,
    _In_
    WDFCMRESLIST Resources
    );

typedef EVT_WDF_DEVICE_RESOURCES_QUERY *PFN_WDF_DEVICE_RESOURCES_QUERY;

typedef
_Function_class_(EVT_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY(
    _In_
    WDFDEVICE Device,
    _In_
    WDFIORESREQLIST IoResourceRequirementsList
    );

typedef EVT_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY *PFN_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY;

typedef
_Function_class_(EVT_WDF_DEVICE_EJECT)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_DEVICE_EJECT(
    _In_
    WDFDEVICE Device
    );

typedef EVT_WDF_DEVICE_EJECT *PFN_WDF_DEVICE_EJECT;

typedef
_Function_class_(EVT_WDF_DEVICE_SET_LOCK)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_DEVICE_SET_LOCK(
    _In_
    WDFDEVICE Device,
    _In_
    BOOLEAN IsLocked
    );

typedef EVT_WDF_DEVICE_SET_LOCK *PFN_WDF_DEVICE_SET_LOCK;

typedef
_Function_class_(EVT_WDF_DEVICE_ENABLE_WAKE_AT_BUS)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_DEVICE_ENABLE_WAKE_AT_BUS(
    _In_
    WDFDEVICE Device,
    _In_
    SYSTEM_POWER_STATE PowerState
    );

typedef EVT_WDF_DEVICE_ENABLE_WAKE_AT_BUS *PFN_WDF_DEVICE_ENABLE_WAKE_AT_BUS;

typedef
_Function_class_(EVT_WDF_DEVICE_DISABLE_WAKE_AT_BUS)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
EVT_WDF_DEVICE_DISABLE_WAKE_AT_BUS(
    _In_
    WDFDEVICE Device
    );

typedef EVT_WDF_DEVICE_DISABLE_WAKE_AT_BUS *PFN_WDF_DEVICE_DISABLE_WAKE_AT_BUS;

typedef struct _WDF_PDO_EVENT_CALLBACKS {
    //
    // The size of this structure in bytes
    //
    ULONG Size;

    //
    // Called in response to IRP_MN_QUERY_RESOURCES
    //
    PFN_WDF_DEVICE_RESOURCES_QUERY EvtDeviceResourcesQuery;

    //
    // Called in response to IRP_MN_QUERY_RESOURCE_REQUIREMENTS
    //
    PFN_WDF_DEVICE_RESOURCE_REQUIREMENTS_QUERY EvtDeviceResourceRequirementsQuery;

    //
    // Called in response to IRP_MN_EJECT
    //
    PFN_WDF_DEVICE_EJECT EvtDeviceEject;

    //
    // Called in response to IRP_MN_SET_LOCK
    //
    PFN_WDF_DEVICE_SET_LOCK EvtDeviceSetLock;

    //
    // Called in response to the power policy owner sending a wait wake to the
    // PDO.  Bus generic arming shoulding occur here.
    //
    PFN_WDF_DEVICE_ENABLE_WAKE_AT_BUS       EvtDeviceEnableWakeAtBus;

    //
    // Called in response to the power policy owner sending a wait wake to the
    // PDO.  Bus generic disarming shoulding occur here.
    //
    PFN_WDF_DEVICE_DISABLE_WAKE_AT_BUS      EvtDeviceDisableWakeAtBus;

} WDF_PDO_EVENT_CALLBACKS, *PWDF_PDO_EVENT_CALLBACKS;

VOID
FORCEINLINE
WDF_PDO_EVENT_CALLBACKS_INIT(
    _Out_ PWDF_PDO_EVENT_CALLBACKS Callbacks
    )
{
    RtlZeroMemory(Callbacks, sizeof(WDF_PDO_EVENT_CALLBACKS));
    Callbacks->Size = sizeof(WDF_PDO_EVENT_CALLBACKS);
}

//
// WDF Function: WdfPdoInitAllocate
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
PWDFDEVICE_INIT
(*PFN_WDFPDOINITALLOCATE)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE ParentDevice
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
PWDFDEVICE_INIT
FORCEINLINE
WdfPdoInitAllocate(
    _In_
    WDFDEVICE ParentDevice
    )
{
    return ((PFN_WDFPDOINITALLOCATE) WdfFunctions[WdfPdoInitAllocateTableIndex])(WdfDriverGlobals, ParentDevice);
}

//
// WDF Function: WdfPdoInitSetEventCallbacks
//
typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
VOID
(*PFN_WDFPDOINITSETEVENTCALLBACKS)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PWDF_PDO_EVENT_CALLBACKS DispatchTable
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
FORCEINLINE
WdfPdoInitSetEventCallbacks(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PWDF_PDO_EVENT_CALLBACKS DispatchTable
    )
{
    ((PFN_WDFPDOINITSETEVENTCALLBACKS) WdfFunctions[WdfPdoInitSetEventCallbacksTableIndex])(WdfDriverGlobals, DeviceInit, DispatchTable);
}

//
// WDF Function: WdfPdoInitAssignDeviceID
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOINITASSIGNDEVICEID)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING DeviceID
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoInitAssignDeviceID(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING DeviceID
    )
{
    return ((PFN_WDFPDOINITASSIGNDEVICEID) WdfFunctions[WdfPdoInitAssignDeviceIDTableIndex])(WdfDriverGlobals, DeviceInit, DeviceID);
}

//
// WDF Function: WdfPdoInitAssignInstanceID
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOINITASSIGNINSTANCEID)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING InstanceID
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoInitAssignInstanceID(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING InstanceID
    )
{
    return ((PFN_WDFPDOINITASSIGNINSTANCEID) WdfFunctions[WdfPdoInitAssignInstanceIDTableIndex])(WdfDriverGlobals, DeviceInit, InstanceID);
}

//
// WDF Function: WdfPdoInitAddHardwareID
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOINITADDHARDWAREID)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING HardwareID
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoInitAddHardwareID(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING HardwareID
    )
{
    return ((PFN_WDFPDOINITADDHARDWAREID) WdfFunctions[WdfPdoInitAddHardwareIDTableIndex])(WdfDriverGlobals, DeviceInit, HardwareID);
}

//
// WDF Function: WdfPdoInitAddCompatibleID
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOINITADDCOMPATIBLEID)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING CompatibleID
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoInitAddCompatibleID(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING CompatibleID
    )
{
    return ((PFN_WDFPDOINITADDCOMPATIBLEID) WdfFunctions[WdfPdoInitAddCompatibleIDTableIndex])(WdfDriverGlobals, DeviceInit, CompatibleID);
}

//
// WDF Function: WdfPdoInitAssignContainerID
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOINITASSIGNCONTAINERID)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING ContainerID
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoInitAssignContainerID(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING ContainerID
    )
{
    return ((PFN_WDFPDOINITASSIGNCONTAINERID) WdfFunctions[WdfPdoInitAssignContainerIDTableIndex])(WdfDriverGlobals, DeviceInit, ContainerID);
}

//
// WDF Function: WdfPdoInitAddDeviceText
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOINITADDDEVICETEXT)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING DeviceDescription,
    _In_
    PCUNICODE_STRING DeviceLocation,
    _In_
    LCID LocaleId
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoInitAddDeviceText(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    PCUNICODE_STRING DeviceDescription,
    _In_
    PCUNICODE_STRING DeviceLocation,
    _In_
    LCID LocaleId
    )
{
    return ((PFN_WDFPDOINITADDDEVICETEXT) WdfFunctions[WdfPdoInitAddDeviceTextTableIndex])(WdfDriverGlobals, DeviceInit, DeviceDescription, DeviceLocation, LocaleId);
}

//
// WDF Function: WdfPdoInitSetDefaultLocale
//
typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
VOID
(*PFN_WDFPDOINITSETDEFAULTLOCALE)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    LCID LocaleId
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
FORCEINLINE
WdfPdoInitSetDefaultLocale(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    LCID LocaleId
    )
{
    ((PFN_WDFPDOINITSETDEFAULTLOCALE) WdfFunctions[WdfPdoInitSetDefaultLocaleTableIndex])(WdfDriverGlobals, DeviceInit, LocaleId);
}

//
// WDF Function: WdfPdoInitAssignRawDevice
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOINITASSIGNRAWDEVICE)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    CONST GUID* DeviceClassGuid
    );

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoInitAssignRawDevice(
    _In_
    PWDFDEVICE_INIT DeviceInit,
    _In_
    CONST GUID* DeviceClassGuid
    )
{
    return ((PFN_WDFPDOINITASSIGNRAWDEVICE) WdfFunctions[WdfPdoInitAssignRawDeviceTableIndex])(WdfDriverGlobals, DeviceInit, DeviceClassGuid);
}

//
// WDF Function: WdfPdoInitAllowForwardingRequestToParent
//
typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
WDFAPI
VOID
(*PFN_WDFPDOINITALLOWFORWARDINGREQUESTTOPARENT)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    PWDFDEVICE_INIT DeviceInit
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID
FORCEINLINE
WdfPdoInitAllowForwardingRequestToParent(
    _In_
    PWDFDEVICE_INIT DeviceInit
    )
{
    ((PFN_WDFPDOINITALLOWFORWARDINGREQUESTTOPARENT) WdfFunctions[WdfPdoInitAllowForwardingRequestToParentTableIndex])(WdfDriverGlobals, DeviceInit);
}

//
// WDF Function: WdfPdoMarkMissing
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOMARKMISSING)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoMarkMissing(
    _In_
    WDFDEVICE Device
    )
{
    return ((PFN_WDFPDOMARKMISSING) WdfFunctions[WdfPdoMarkMissingTableIndex])(WdfDriverGlobals, Device);
}

//
// WDF Function: WdfPdoRequestEject
//
typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
VOID
(*PFN_WDFPDOREQUESTEJECT)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FORCEINLINE
WdfPdoRequestEject(
    _In_
    WDFDEVICE Device
    )
{
    ((PFN_WDFPDOREQUESTEJECT) WdfFunctions[WdfPdoRequestEjectTableIndex])(WdfDriverGlobals, Device);
}

//
// WDF Function: WdfPdoGetParent
//
typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
WDFDEVICE
(*PFN_WDFPDOGETPARENT)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
WDFDEVICE
FORCEINLINE
WdfPdoGetParent(
    _In_
    WDFDEVICE Device
    )
{
    return ((PFN_WDFPDOGETPARENT) WdfFunctions[WdfPdoGetParentTableIndex])(WdfDriverGlobals, Device);
}

//
// WDF Function: WdfPdoRetrieveIdentificationDescription
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDORETRIEVEIDENTIFICATIONDESCRIPTION)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device,
    _Inout_
    PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoRetrieveIdentificationDescription(
    _In_
    WDFDEVICE Device,
    _Inout_
    PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription
    )
{
    return ((PFN_WDFPDORETRIEVEIDENTIFICATIONDESCRIPTION) WdfFunctions[WdfPdoRetrieveIdentificationDescriptionTableIndex])(WdfDriverGlobals, Device, IdentificationDescription);
}

//
// WDF Function: WdfPdoRetrieveAddressDescription
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDORETRIEVEADDRESSDESCRIPTION)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device,
    _Inout_
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoRetrieveAddressDescription(
    _In_
    WDFDEVICE Device,
    _Inout_
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
    )
{
    return ((PFN_WDFPDORETRIEVEADDRESSDESCRIPTION) WdfFunctions[WdfPdoRetrieveAddressDescriptionTableIndex])(WdfDriverGlobals, Device, AddressDescription);
}

//
// WDF Function: WdfPdoUpdateAddressDescription
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOUPDATEADDRESSDESCRIPTION)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device,
    _Inout_
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoUpdateAddressDescription(
    _In_
    WDFDEVICE Device,
    _Inout_
    PWDF_CHILD_ADDRESS_DESCRIPTION_HEADER AddressDescription
    )
{
    return ((PFN_WDFPDOUPDATEADDRESSDESCRIPTION) WdfFunctions[WdfPdoUpdateAddressDescriptionTableIndex])(WdfDriverGlobals, Device, AddressDescription);
}

//
// WDF Function: WdfPdoAddEjectionRelationsPhysicalDevice
//
typedef
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
NTSTATUS
(*PFN_WDFPDOADDEJECTIONRELATIONSPHYSICALDEVICE)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device,
    _In_
    PDEVICE_OBJECT PhysicalDevice
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
FORCEINLINE
WdfPdoAddEjectionRelationsPhysicalDevice(
    _In_
    WDFDEVICE Device,
    _In_
    PDEVICE_OBJECT PhysicalDevice
    )
{
    return ((PFN_WDFPDOADDEJECTIONRELATIONSPHYSICALDEVICE) WdfFunctions[WdfPdoAddEjectionRelationsPhysicalDeviceTableIndex])(WdfDriverGlobals, Device, PhysicalDevice);
}

//
// WDF Function: WdfPdoRemoveEjectionRelationsPhysicalDevice
//
typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
VOID
(*PFN_WDFPDOREMOVEEJECTIONRELATIONSPHYSICALDEVICE)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device,
    _In_
    PDEVICE_OBJECT PhysicalDevice
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FORCEINLINE
WdfPdoRemoveEjectionRelationsPhysicalDevice(
    _In_
    WDFDEVICE Device,
    _In_
    PDEVICE_OBJECT PhysicalDevice
    )
{
    ((PFN_WDFPDOREMOVEEJECTIONRELATIONSPHYSICALDEVICE) WdfFunctions[WdfPdoRemoveEjectionRelationsPhysicalDeviceTableIndex])(WdfDriverGlobals, Device, PhysicalDevice);
}

//
// WDF Function: WdfPdoClearEjectionRelationsDevices
//
typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
WDFAPI
VOID
(*PFN_WDFPDOCLEAREJECTIONRELATIONSDEVICES)(
    _In_
    PWDF_DRIVER_GLOBALS DriverGlobals,
    _In_
    WDFDEVICE Device
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FORCEINLINE
WdfPdoClearEjectionRelationsDevices(
    _In_
    WDFDEVICE Device
    )
{
    ((PFN_WDFPDOCLEAREJECTIONRELATIONSDEVICES) WdfFunctions[WdfPdoClearEjectionRelationsDevicesTableIndex])(WdfDriverGlobals, Device);
}



#endif // (NTDDI_VERSION >= NTDDI_WIN2K)


#endif // _WDFPDO_1_9_H_
