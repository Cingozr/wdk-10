/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    WdfWMI.h

Environment:

    user mode

NOTE: This header is generated by stubwork.

      To modify contents, add or remove <shared> or <umdf>
      tags in the corresponding .x and .y template files.

--*/

#pragma once

#ifndef WDF_EXTERN_C
  #ifdef __cplusplus
    #define WDF_EXTERN_C       extern "C"
    #define WDF_EXTERN_C_START extern "C" {
    #define WDF_EXTERN_C_END   }
  #else
    #define WDF_EXTERN_C
    #define WDF_EXTERN_C_START
    #define WDF_EXTERN_C_END
  #endif
#endif

WDF_EXTERN_C_START

typedef enum _WDF_WMI_PROVIDER_CONTROL {
    WdfWmiControlInvalid = 0,
    WdfWmiEventControl,
    WdfWmiInstanceControl,
} WDF_WMI_PROVIDER_CONTROL;

// 
// WdfWmiProviderExpensive:
// The provider's operations are expensive in terms of resources
// 
// WdfWmiProviderReadOnly:
// The provider is read only. No set or set data item callbacks will be
// made on all instances of this provider.
// 
// WdfWmiProviderEventOnly:
// Data item is being used to fire events only.  It will not receive any
// callbacks on it to get / set / execute buffers.
// 
typedef enum _WDF_WMI_PROVIDER_FLAGS {
    WdfWmiProviderEventOnly = 0x0001,
    WdfWmiProviderExpensive = 0x0002,
    WdfWmiProviderTracing =   0x0004,
    WdfWmiProviderValidFlags = WdfWmiProviderEventOnly | WdfWmiProviderExpensive | WdfWmiProviderTracing,
} WDF_WMI_PROVIDER_FLAGS;



typedef
_Function_class_(EVT_WDF_WMI_INSTANCE_QUERY_INSTANCE)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_WMI_INSTANCE_QUERY_INSTANCE(
    _In_
    WDFWMIINSTANCE WmiInstance,
    _In_
    ULONG OutBufferSize,
    _Out_writes_bytes_to_(OutBufferSize, *BufferUsed)
    PVOID OutBuffer,
    _Out_
    PULONG BufferUsed
    );

typedef EVT_WDF_WMI_INSTANCE_QUERY_INSTANCE *PFN_WDF_WMI_INSTANCE_QUERY_INSTANCE;

typedef
_Function_class_(EVT_WDF_WMI_INSTANCE_SET_INSTANCE)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_WMI_INSTANCE_SET_INSTANCE(
    _In_
    WDFWMIINSTANCE WmiInstance,
    _In_
    ULONG InBufferSize,
    _In_reads_bytes_(InBufferSize)
    PVOID InBuffer
    );

typedef EVT_WDF_WMI_INSTANCE_SET_INSTANCE *PFN_WDF_WMI_INSTANCE_SET_INSTANCE;

typedef
_Function_class_(EVT_WDF_WMI_INSTANCE_SET_ITEM)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_WMI_INSTANCE_SET_ITEM(
    _In_
    WDFWMIINSTANCE WmiInstance,
    _In_
    ULONG DataItemId,
    _In_
    ULONG InBufferSize,
    _In_reads_bytes_(InBufferSize)
    PVOID InBuffer
    );

typedef EVT_WDF_WMI_INSTANCE_SET_ITEM *PFN_WDF_WMI_INSTANCE_SET_ITEM;

typedef
_Function_class_(EVT_WDF_WMI_INSTANCE_EXECUTE_METHOD)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_WMI_INSTANCE_EXECUTE_METHOD(
    _In_
    WDFWMIINSTANCE WmiInstance,
    _In_
    ULONG MethodId,
    _In_
    ULONG InBufferSize,
    _In_
    ULONG OutBufferSize,
    _When_(InBufferSize >= OutBufferSize, _Inout_updates_bytes_(InBufferSize))
    _When_(InBufferSize < OutBufferSize, _Inout_updates_bytes_(OutBufferSize))
    PVOID Buffer,
    _Out_
    PULONG BufferUsed
    );

typedef EVT_WDF_WMI_INSTANCE_EXECUTE_METHOD *PFN_WDF_WMI_INSTANCE_EXECUTE_METHOD;

typedef
_Function_class_(EVT_WDF_WMI_PROVIDER_FUNCTION_CONTROL)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EVT_WDF_WMI_PROVIDER_FUNCTION_CONTROL(
    _In_
    WDFWMIPROVIDER WmiProvider,
    _In_
    WDF_WMI_PROVIDER_CONTROL Control,
    _In_
    BOOLEAN Enable
    );

typedef EVT_WDF_WMI_PROVIDER_FUNCTION_CONTROL *PFN_WDF_WMI_PROVIDER_FUNCTION_CONTROL;

typedef struct _WDF_WMI_PROVIDER_CONFIG {
    //
    // Size of this structure in bytes
    //
    ULONG Size;

    //
    // The GUID being registered
    //
    GUID Guid;

    //
    // Combination of values from the enum WDF_WMI_PROVIDER_FLAGS
    //
    ULONG Flags;

    //
    // Minimum expected buffer size for query and set instance requests.
    // Ignored if WdfWmiProviderEventOnly is set in Flags.
    //
    ULONG MinInstanceBufferSize;

    //
    // Callback when caller is opening a provider which ha been marked as
    // expensive or when a caller is interested in events.
    //
    PFN_WDF_WMI_PROVIDER_FUNCTION_CONTROL EvtWmiProviderFunctionControl;

} WDF_WMI_PROVIDER_CONFIG, *PWDF_WMI_PROVIDER_CONFIG;

VOID
FORCEINLINE
WDF_WMI_PROVIDER_CONFIG_INIT(
    _Out_ PWDF_WMI_PROVIDER_CONFIG Config,
    _In_ CONST GUID* Guid
    )
{
    RtlZeroMemory(Config, sizeof(WDF_WMI_PROVIDER_CONFIG));

    Config->Size = sizeof(WDF_WMI_PROVIDER_CONFIG);
    RtlCopyMemory(&Config->Guid, Guid, sizeof(GUID));
}

typedef struct _WDF_WMI_INSTANCE_CONFIG {
    //
    // Size of the structure in bytes
    //
    ULONG Size;

    //
    // Optional parameter.  If NULL, ProviderConfig must be set to a valid pointer
    // value.   If specified, indicates the provider to create an instance for.
    //
    WDFWMIPROVIDER Provider;

    //
    // Optional parameter.  If NULL, Provider must be set to a valid handle
    // value.  If specifeid, indicates the configuration for a provider to be
    // created and for this instance to be associated with.
    //
    PWDF_WMI_PROVIDER_CONFIG ProviderConfig;

    //
    // If the Provider is configured as read only and this field is set to TRUE,
    // the EvtWmiInstanceQueryInstance is ignored and WDF will blindly copy the
    // context associated with this instance (using RtlCopyMemory, with no locks
    // held) into the query buffer.
    //
    BOOLEAN UseContextForQuery;

    //
    // If TRUE, the instance will be registered as well as created.
    //
    BOOLEAN Register;

    //
    // Callback when caller wants to query the entire data item's buffer.
    //
    PFN_WDF_WMI_INSTANCE_QUERY_INSTANCE EvtWmiInstanceQueryInstance;

    //
    // Callback when caller wants to set the entire data item's buffer.
    //
    PFN_WDF_WMI_INSTANCE_SET_INSTANCE EvtWmiInstanceSetInstance;

    //
    // Callback when caller wants to set a single field in the data item's buffer
    //
    PFN_WDF_WMI_INSTANCE_SET_ITEM EvtWmiInstanceSetItem;

    //
    // Callback when caller wants to execute a method on the data item.
    //
    PFN_WDF_WMI_INSTANCE_EXECUTE_METHOD EvtWmiInstanceExecuteMethod;

} WDF_WMI_INSTANCE_CONFIG, *PWDF_WMI_INSTANCE_CONFIG;

WDF_EXTERN_C_END

