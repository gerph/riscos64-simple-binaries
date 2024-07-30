#ifndef SWI_NUMBERS_H
#define SWI_NUMBERS_H

#undef ADFS_DiscOp
#define ADFS_DiscOp                              0x00040240
#undef ADFS_HDC
#define ADFS_HDC                                 0x00040241
#undef ADFS_Drives
#define ADFS_Drives                              0x00040242
#undef ADFS_FreeSpace
#define ADFS_FreeSpace                           0x00040243
#undef ADFS_Retries
#define ADFS_Retries                             0x00040244
#undef ADFS_DescribeDisc
#define ADFS_DescribeDisc                        0x00040245
#undef ADFS_VetFormat
#define ADFS_VetFormat                           0x00040246
#undef ADFS_FlpProcessDCB
#define ADFS_FlpProcessDCB                       0x00040247
#undef ADFS_ControllerType
#define ADFS_ControllerType                      0x00040248
#undef ADFS_PowerControl
#define ADFS_PowerControl                        0x00040249
#undef ADFS_SetIDEController
#define ADFS_SetIDEController                    0x0004024A
#undef ADFS_IDEUserOp
#define ADFS_IDEUserOp                           0x0004024B
#undef ADFS_MiscOp
#define ADFS_MiscOp                              0x0004024C /*  &4024C */
#undef ADFS_SectorDiscOp
#define ADFS_SectorDiscOp                        0x0004024D /*  &4024D */
#undef ADFS_NOP2
#define ADFS_NOP2                                0x0004024E /*  &4024E */
#undef ADFS_NOP3
#define ADFS_NOP3                                0x0004024F /*  &4024F */
#undef ADFS_ECCSAndRetries
#define ADFS_ECCSAndRetries                      0x00040250 /*  &40250 */
#undef ADFS_LockIDE
#define ADFS_LockIDE                             0x00040251 /*  &40251 */
#undef ADFS_FreeSpace64
#define ADFS_FreeSpace64                         0x00040252 /*  &40252 */
#undef ATAPI_GetDrives
#define ATAPI_GetDrives                          0x0004A740 /*   +0 */
#undef Buffer_Create
#define Buffer_Create                            0x00042940
#undef Buffer_Remove
#define Buffer_Remove                            0x00042941
#undef Buffer_Register
#define Buffer_Register                          0x00042942
#undef Buffer_Deregister
#define Buffer_Deregister                        0x00042943
#undef Buffer_ModifyFlags
#define Buffer_ModifyFlags                       0x00042944
#undef Buffer_LinkDevice
#define Buffer_LinkDevice                        0x00042945
#undef Buffer_UnlinkDevice
#define Buffer_UnlinkDevice                      0x00042946
#undef Buffer_GetInfo
#define Buffer_GetInfo                           0x00042947
#undef Buffer_Threshold
#define Buffer_Threshold                         0x00042948
#undef Buffer_InternalInfo
#define Buffer_InternalInfo                      0x00042949
#undef Cache_Control
#define Cache_Control                            0x00000280
#undef Cache_Cacheable
#define Cache_Cacheable                          0x00000281
#undef Cache_Updateable
#define Cache_Updateable                         0x00000282
#undef Cache_Disruptive
#define Cache_Disruptive                         0x00000283
#undef Cache_Flush
#define Cache_Flush                              0x00000284
#undef CD_Version
#define CD_Version                               0x00041240 /*   +0 */
#undef CD_ReadData
#define CD_ReadData                              0x00041241 /*   +1 */
#undef CD_SeekTo
#define CD_SeekTo                                0x00041242 /*   +2 */
#undef CD_DriveStatus
#define CD_DriveStatus                           0x00041243 /*   +3 */
#undef CD_DriveReady
#define CD_DriveReady                            0x00041244 /*   +4 */
#undef CD_GetParameters
#define CD_GetParameters                         0x00041245 /*   +5     Private */
#undef CD_SetParameters
#define CD_SetParameters                         0x00041246 /*   +6     Private */
#undef CD_OpenDrawer
#define CD_OpenDrawer                            0x00041247 /*   +7 */
#undef CD_EjectButton
#define CD_EjectButton                           0x00041248 /*   +8 */
#undef CD_EnquireAddress
#define CD_EnquireAddress                        0x00041249 /*   +9 */
#undef CD_EnquireDataMode
#define CD_EnquireDataMode                       0x0004124A /*  +10     Private */
#undef CD_PlayAudio
#define CD_PlayAudio                             0x0004124B /*  +11 */
#undef CD_PlayTrack
#define CD_PlayTrack                             0x0004124C /*  +12 */
#undef CD_AudioPause
#define CD_AudioPause                            0x0004124D /*  +13 */
#undef CD_EnquireTrack
#define CD_EnquireTrack                          0x0004124E /*  +14 */
#undef CD_ReadSubChannel
#define CD_ReadSubChannel                        0x0004124F /*  +15     Private */
#undef CD_CheckDrive
#define CD_CheckDrive                            0x00041250 /*  +16 */
#undef CD_DiscChanged
#define CD_DiscChanged                           0x00041251 /*  +17     Private */
#undef CD_StopDisc
#define CD_StopDisc                              0x00041252 /*  +18 */
#undef CD_DiscUsed
#define CD_DiscUsed                              0x00041253 /*  +19 */
#undef CD_AudioStatus
#define CD_AudioStatus                           0x00041254 /*  +20 */
#undef CD_Inquiry
#define CD_Inquiry                               0x00041255 /*  +21 */
#undef CD_DiscHasChanged
#define CD_DiscHasChanged                        0x00041256 /*  +22     Private */
#undef CD_Control
#define CD_Control                               0x00041257 /*  +23 */
#undef CD_Supported
#define CD_Supported                             0x00041258 /*  +24     Private */
#undef CD_Prefetch
#define CD_Prefetch                              0x00041259 /*  +25 */
#undef CD_Reset
#define CD_Reset                                 0x0004125A /*  +26 */
#undef CD_CloseDrawer
#define CD_CloseDrawer                           0x0004125B /*  +27     Private */
#undef CD_IsDrawerLocked
#define CD_IsDrawerLocked                        0x0004125C /*  +28     Private */
#undef CD_AudioControl
#define CD_AudioControl                          0x0004125D /*  +29     Private */
#undef CD_LastError
#define CD_LastError                             0x0004125E /*  +30 */
#undef CD_AudioLevel
#define CD_AudioLevel                            0x0004125F /*  +31     Private */
#undef CD_Register
#define CD_Register                              0x00041260 /*  +32 */
#undef CD_Unregister
#define CD_Unregister                            0x00041261 /*  +33 */
#undef CD_ByteCopy
#define CD_ByteCopy                              0x00041262 /*  +34     Private */
#undef CD_Identify
#define CD_Identify                              0x00041263 /*  +35 */
#undef CD_ConvertToLBA
#define CD_ConvertToLBA                          0x00041264 /*  +36 */
#undef CD_ConvertToMSF
#define CD_ConvertToMSF                          0x00041265 /*  +37 */
#undef CD_ReadAudio
#define CD_ReadAudio                             0x00041266 /*  +38 */
#undef CD_ReadUserData
#define CD_ReadUserData                          0x00041267 /*  +39 */
#undef CD_SeekUserData
#define CD_SeekUserData                          0x00041268 /*  +40 */
#undef CD_GetAudioParms
#define CD_GetAudioParms                         0x00041269 /*  +41 */
#undef CD_SetAudioParms
#define CD_SetAudioParms                         0x0004126A /*  +42 */
#undef CDFS_ConvertDriveToDevice
#define CDFS_ConvertDriveToDevice                0x00041E80
#undef CDFS_SetBufferSize
#define CDFS_SetBufferSize                       0x00041E81
#undef CDFS_GetBufferSize
#define CDFS_GetBufferSize                       0x00041E82
#undef CDFS_SetNumberOfDrives
#define CDFS_SetNumberOfDrives                   0x00041E83
#undef CDFS_GetNumberOfDrives
#define CDFS_GetNumberOfDrives                   0x00041E84
#undef CDFS_GiveFileType
#define CDFS_GiveFileType                        0x00041E85
#undef CDFS_DescribeDisc
#define CDFS_DescribeDisc                        0x00041E86
#undef ColourPicker_RegisterModel
#define ColourPicker_RegisterModel               0x00047700
#undef ColourPicker_DeregisterModel
#define ColourPicker_DeregisterModel             0x00047701
#undef ColourPicker_OpenDialogue
#define ColourPicker_OpenDialogue                0x00047702
#undef ColourPicker_CloseDialogue
#define ColourPicker_CloseDialogue               0x00047703
#undef ColourPicker_UpdateDialogue
#define ColourPicker_UpdateDialogue              0x00047704
#undef ColourPicker_ReadDialogue
#define ColourPicker_ReadDialogue                0x00047705
#undef ColourPicker_SetColour
#define ColourPicker_SetColour                   0x00047706
#undef ColourPicker_HelpReply
#define ColourPicker_HelpReply                   0x00047707
#undef ColourPicker_ModelSWI
#define ColourPicker_ModelSWI                    0x00047708
#undef ColourTrans_SelectTable
#define ColourTrans_SelectTable                  0x00040740 /*  &40740 */
#undef ColourTrans_SelectGCOLTable
#define ColourTrans_SelectGCOLTable              0x00040741 /*  &40741 */
#undef ColourTrans_ReturnGCOL
#define ColourTrans_ReturnGCOL                   0x00040742 /*  &40742 */
#undef ColourTrans_SetGCOL
#define ColourTrans_SetGCOL                      0x00040743 /*  &40743 */
#undef ColourTrans_ReturnColourNumber
#define ColourTrans_ReturnColourNumber           0x00040744 /*  &40744 */
#undef ColourTrans_ReturnGCOLForMode
#define ColourTrans_ReturnGCOLForMode            0x00040745 /*  &40745 */
#undef ColourTrans_ReturnColourNumberForMode
#define ColourTrans_ReturnColourNumberForMode    0x00040746 /*  &40746 */
#undef ColourTrans_ReturnOppGCOL
#define ColourTrans_ReturnOppGCOL                0x00040747 /*  &40747 */
#undef ColourTrans_SetOppGCOL
#define ColourTrans_SetOppGCOL                   0x00040748 /*  &40748 */
#undef ColourTrans_ReturnOppColourNumber
#define ColourTrans_ReturnOppColourNumber        0x00040749 /*  &40749 */
#undef ColourTrans_ReturnOppGCOLForMode
#define ColourTrans_ReturnOppGCOLForMode         0x0004074A /*  &4074A */
#undef ColourTrans_ReturnOppColourNumberForMode
#define ColourTrans_ReturnOppColourNumberForMode 0x0004074B /*  &4074B */
#undef ColourTrans_GCOLToColourNumber
#define ColourTrans_GCOLToColourNumber           0x0004074C /*  &4074C */
#undef ColourTrans_ColourNumberToGCOL
#define ColourTrans_ColourNumberToGCOL           0x0004074D /*  &4074D */
#undef ColourTrans_ReturnFontColours
#define ColourTrans_ReturnFontColours            0x0004074E /*  &4074E */
#undef ColourTrans_SetFontColours
#define ColourTrans_SetFontColours               0x0004074F /*  &4074F */
#undef ColourTrans_InvalidateCache
#define ColourTrans_InvalidateCache              0x00040750 /*  &40750 */
#undef ColourTrans_SetCalibration
#define ColourTrans_SetCalibration               0x00040751 /*  &40751 */
#undef ColourTrans_ReadCalibration
#define ColourTrans_ReadCalibration              0x00040752 /*  &40752 */
#undef ColourTrans_ConvertDeviceColour
#define ColourTrans_ConvertDeviceColour          0x00040753 /*  &40753 */
#undef ColourTrans_ConvertDevicePalette
#define ColourTrans_ConvertDevicePalette         0x00040754 /*  &40754 */
#undef ColourTrans_ConvertRGBToCIE
#define ColourTrans_ConvertRGBToCIE              0x00040755 /*  &40755 */
#undef ColourTrans_ConvertCIEToRGB
#define ColourTrans_ConvertCIEToRGB              0x00040756 /*  &40756 */
#undef ColourTrans_WriteCalibrationToFile
#define ColourTrans_WriteCalibrationToFile       0x00040757 /*  &40757 */
#undef ColourTrans_ConvertRGBToHSV
#define ColourTrans_ConvertRGBToHSV              0x00040758 /*  &40758 */
#undef ColourTrans_ConvertHSVToRGB
#define ColourTrans_ConvertHSVToRGB              0x00040759 /*  &40759 */
#undef ColourTrans_ConvertRGBToCMYK
#define ColourTrans_ConvertRGBToCMYK             0x0004075A /*  &4075A */
#undef ColourTrans_ConvertCMYKToRGB
#define ColourTrans_ConvertCMYKToRGB             0x0004075B /*  &4075B */
#undef ColourTrans_ReadPalette
#define ColourTrans_ReadPalette                  0x0004075C /*  &4075C */
#undef ColourTrans_WritePalette
#define ColourTrans_WritePalette                 0x0004075D /*  &4075D */
#undef ColourTrans_SetColour
#define ColourTrans_SetColour                    0x0004075E /*  &4075E */
#undef ColourTrans_MiscOp
#define ColourTrans_MiscOp                       0x0004075F /*  &4075F */
#undef ColourTrans_WriteLoadingsToFile
#define ColourTrans_WriteLoadingsToFile          0x00040760 /*  &40760 */
#undef ColourTrans_SetTextColour
#define ColourTrans_SetTextColour                0x00040761 /*  &40761 */
#undef ColourTrans_SetOppTextColour
#define ColourTrans_SetOppTextColour             0x00040762 /*  &40762 */
#undef ColourTrans_GenerateTable
#define ColourTrans_GenerateTable                0x00040763 /*  &40763 */
#undef Debugger_Disassemble
#define Debugger_Disassemble                     0x00040380
#undef Debugger_DisassembleThumb
#define Debugger_DisassembleThumb                0x00040381
#undef DeviceFS_Register
#define DeviceFS_Register                        0x00042740
#undef DeviceFS_Deregister
#define DeviceFS_Deregister                      0x00042741
#undef DeviceFS_RegisterObjects
#define DeviceFS_RegisterObjects                 0x00042742
#undef DeviceFS_DeregisterObjects
#define DeviceFS_DeregisterObjects               0x00042743
#undef DeviceFS_CallDevice
#define DeviceFS_CallDevice                      0x00042744
#undef DeviceFS_Threshold
#define DeviceFS_Threshold                       0x00042745
#undef DeviceFS_ReceivedCharacter
#define DeviceFS_ReceivedCharacter               0x00042746
#undef DeviceFS_TransmitCharacter
#define DeviceFS_TransmitCharacter               0x00042747
#undef DMA_RegisterChannel
#define DMA_RegisterChannel                      0x00046140
#undef DMA_DeregisterChannel
#define DMA_DeregisterChannel                    0x00046141
#undef DMA_QueueTransfer
#define DMA_QueueTransfer                        0x00046142
#undef DMA_TerminateTransfer
#define DMA_TerminateTransfer                    0x00046143
#undef DMA_SuspendTransfer
#define DMA_SuspendTransfer                      0x00046144
#undef DMA_ResumeTransfer
#define DMA_ResumeTransfer                       0x00046145
#undef DMA_ExamineTransfer
#define DMA_ExamineTransfer                      0x00046146
#undef DragASprite_Start
#define DragASprite_Start                        0x00042400 /*  &42500 */
#undef DragASprite_Stop
#define DragASprite_Stop                         0x00042401 /*  &42501 */
#undef DragAnObject_Start
#define DragAnObject_Start                       0x00049C40
#undef DragAnObject_Stop
#define DragAnObject_Stop                        0x00049C41
#undef Draw_ProcessPath
#define Draw_ProcessPath                         0x00040700 /*  &40700 */
#undef Draw_ProcessPathFP
#define Draw_ProcessPathFP                       0x00040701 /*  &40701 */
#undef Draw_Fill
#define Draw_Fill                                0x00040702 /*  &40702 */
#undef Draw_FillFP
#define Draw_FillFP                              0x00040703 /*  &40703 */
#undef Draw_Stroke
#define Draw_Stroke                              0x00040704 /*  &40704 */
#undef Draw_StrokeFP
#define Draw_StrokeFP                            0x00040705 /*  &40705 */
#undef Draw_StrokePath
#define Draw_StrokePath                          0x00040706 /*  &40706 */
#undef Draw_StrokePathFP
#define Draw_StrokePathFP                        0x00040707 /*  &40707 */
#undef Draw_FlattenPath
#define Draw_FlattenPath                         0x00040708 /*  &40708 */
#undef Draw_FlattenPathFP
#define Draw_FlattenPathFP                       0x00040709 /*  &40709 */
#undef Draw_TransformPath
#define Draw_TransformPath                       0x0004070A /*  &4070A */
#undef Draw_TransformPathFP
#define Draw_TransformPathFP                     0x0004070B /*  &4070B */
#undef Draw_FillClipped
#define Draw_FillClipped                         0x0004070C /*  &4070C */
#undef Draw_FillClippedFP
#define Draw_FillClippedFP                       0x0004070D /*  &4070D */
#undef Draw_StrokeClipped
#define Draw_StrokeClipped                       0x0004070E /*  &4070E */
#undef Draw_StrokeClippedFP
#define Draw_StrokeClippedFP                     0x0004070F /*  &4070F */
#undef Econet_CreateReceive
#define Econet_CreateReceive                     0x00040000 /*  40000 */
#undef Econet_ExamineReceive
#define Econet_ExamineReceive                    0x00040001 /*  40001 */
#undef Econet_ReadReceive
#define Econet_ReadReceive                       0x00040002 /*  40002 */
#undef Econet_AbandonReceive
#define Econet_AbandonReceive                    0x00040003 /*  40003 */
#undef Econet_WaitForReception
#define Econet_WaitForReception                  0x00040004 /*  40004 */
#undef Econet_EnumerateReceive
#define Econet_EnumerateReceive                  0x00040005 /*  40005 */
#undef Econet_StartTransmit
#define Econet_StartTransmit                     0x00040006 /*  40006 */
#undef Econet_PollTransmit
#define Econet_PollTransmit                      0x00040007 /*  40007 */
#undef Econet_AbandonTransmit
#define Econet_AbandonTransmit                   0x00040008 /*  40008 */
#undef Econet_DoTransmit
#define Econet_DoTransmit                        0x00040009 /*  40009 */
#undef Econet_ReadLocalStationAndNet
#define Econet_ReadLocalStationAndNet            0x0004000A /*  4000A */
#undef Econet_ConvertStatusToString
#define Econet_ConvertStatusToString             0x0004000B /*  4000B */
#undef Econet_ConvertStatusToError
#define Econet_ConvertStatusToError              0x0004000C /*  4000C */
#undef Econet_ReadProtection
#define Econet_ReadProtection                    0x0004000D /*  4000D */
#undef Econet_SetProtection
#define Econet_SetProtection                     0x0004000E /*  4000E */
#undef Econet_ReadStationNumber
#define Econet_ReadStationNumber                 0x0004000F /*  4000F */
#undef Econet_PrintBanner
#define Econet_PrintBanner                       0x00040010 /*  40010 */
#undef Econet_ReadTransportType
#define Econet_ReadTransportType                 0x00040011 /*  40011 */
#undef Econet_ReleasePort
#define Econet_ReleasePort                       0x00040012 /*  40012 */
#undef Econet_AllocatePort
#define Econet_AllocatePort                      0x00040013 /*  40013 */
#undef Econet_DeAllocatePort
#define Econet_DeAllocatePort                    0x00040014 /*  40014 */
#undef Econet_ClaimPort
#define Econet_ClaimPort                         0x00040015 /*  40015 */
#undef Econet_StartImmediate
#define Econet_StartImmediate                    0x00040016 /*  40016 */
#undef Econet_DoImmediate
#define Econet_DoImmediate                       0x00040017 /*  40017 */
#undef Econet_AbandonAndReadReceive
#define Econet_AbandonAndReadReceive             0x00040018 /*  40018 */
#undef Econet_Version
#define Econet_Version                           0x00040019 /*  40019 */
#undef Econet_NetworkState
#define Econet_NetworkState                      0x0004001A /*  4001A */
#undef Econet_PacketSize
#define Econet_PacketSize                        0x0004001B /*  4001B */
#undef Econet_ReadTransportName
#define Econet_ReadTransportName                 0x0004001C /*  4001C */
#undef Econet_InetRxDirect
#define Econet_InetRxDirect                      0x0004001D /*  4001D */
#undef Econet_EnumerateMap
#define Econet_EnumerateMap                      0x0004001E /*  4001E */
#undef Econet_EnumerateTransmit
#define Econet_EnumerateTransmit                 0x0004001F /*  4001F */
#undef Econet_HardwareAddresses
#define Econet_HardwareAddresses                 0x00040020 /*  40020 */
#undef Econet_NetworkParameters
#define Econet_NetworkParameters                 0x00040021 /*  40021 */
#undef NetFS_ReadFSNumber
#define NetFS_ReadFSNumber                       0x00040040 /*  40040 */
#undef NetFS_SetFSNumber
#define NetFS_SetFSNumber                        0x00040041 /*  40041 */
#undef NetFS_ReadFSName
#define NetFS_ReadFSName                         0x00040042 /*  40042 */
#undef NetFS_SetFSName
#define NetFS_SetFSName                          0x00040043 /*  40043 */
#undef NetFS_ReadCurrentContext
#define NetFS_ReadCurrentContext                 0x00040044 /*  40044 */
#undef NetFS_SetCurrentContext
#define NetFS_SetCurrentContext                  0x00040045 /*  40045 */
#undef NetFS_ReadFSTimeouts
#define NetFS_ReadFSTimeouts                     0x00040046 /*  40046 */
#undef NetFS_SetFSTimeouts
#define NetFS_SetFSTimeouts                      0x00040047 /*  40047 */
#undef NetFS_DoFSOp
#define NetFS_DoFSOp                             0x00040048 /*  40048 */
#undef NetFS_EnumerateFSList
#define NetFS_EnumerateFSList                    0x00040049 /*  40049 */
#undef NetFS_EnumerateFS
#define NetFS_EnumerateFS                        0x0004004A /*  4004A */
#undef NetFS_ConvertDate
#define NetFS_ConvertDate                        0x0004004B /*  4004B */
#undef NetFS_DoFSOpToGivenFS
#define NetFS_DoFSOpToGivenFS                    0x0004004C /*  4004C */
#undef NetFS_UpdateFSList
#define NetFS_UpdateFSList                       0x0004004D /*  4004D */
#undef NetFS_EnumerateFSContexts
#define NetFS_EnumerateFSContexts                0x0004004E /*  4004E */
#undef NetFS_ReadUserId
#define NetFS_ReadUserId                         0x0004004F /*  4004F */
#undef NetFS_GetObjectUID
#define NetFS_GetObjectUID                       0x00040050 /*  40050 */
#undef NetFS_EnableCache
#define NetFS_EnableCache                        0x00040051 /*  40051 */
#undef NetPrint_ReadPSNumber
#define NetPrint_ReadPSNumber                    0x00040200 /*  40200 */
#undef NetPrint_SetPSNumber
#define NetPrint_SetPSNumber                     0x00040201 /*  40201 */
#undef NetPrint_ReadPSName
#define NetPrint_ReadPSName                      0x00040202 /*  40202 */
#undef NetPrint_SetPSName
#define NetPrint_SetPSName                       0x00040203 /*  40203 */
#undef NetPrint_ReadPSTimeouts
#define NetPrint_ReadPSTimeouts                  0x00040204 /*  40204 */
#undef NetPrint_SetPSTimeouts
#define NetPrint_SetPSTimeouts                   0x00040205 /*  40205 */
#undef NetPrint_BindPSName
#define NetPrint_BindPSName                      0x00040206 /*  40206 */
#undef NetPrint_ListServers
#define NetPrint_ListServers                     0x00040207 /*  40207 */
#undef NetPrint_ConvertStatusToString
#define NetPrint_ConvertStatusToString           0x00040208 /*  40208 */
#undef NetMonitor_PrintChar
#define NetMonitor_PrintChar                     0x00080040 /*  80040 */
#undef NetMonitor_DefineTask
#define NetMonitor_DefineTask                    0x00080041 /*  80041 */
#undef NetMonitor_AbandonTask
#define NetMonitor_AbandonTask                   0x00080042 /*  80042 */
#undef NetMonitor_ConvertFont
#define NetMonitor_ConvertFont                   0x00080043 /*  80043 */
#undef NetMonitor_UseFont
#define NetMonitor_UseFont                       0x00080044 /*  80044 */
#undef NetMonitor_RestoreFont
#define NetMonitor_RestoreFont                   0x00080045 /*  80045 */
#undef NetMonitor_StartWithCurrentFont
#define NetMonitor_StartWithCurrentFont          0x00080046 /*  80046 */
#undef NetMonitor_StartWithInternalFont
#define NetMonitor_StartWithInternalFont         0x00080047 /*  80047 */
#undef FileCore_DiscOp
#define FileCore_DiscOp                          0x00040540
#undef FileCore_Create
#define FileCore_Create                          0x00040541
#undef FileCore_Drives
#define FileCore_Drives                          0x00040542
#undef FileCore_FreeSpace
#define FileCore_FreeSpace                       0x00040543
#undef FileCore_FloppyStructure
#define FileCore_FloppyStructure                 0x00040544
#undef FileCore_DescribeDisc
#define FileCore_DescribeDisc                    0x00040545
#undef FileCore_DiscardReadSectorsCache
#define FileCore_DiscardReadSectorsCache         0x00040546
#undef FileCore_DiscFormat
#define FileCore_DiscFormat                      0x00040547
#undef FileCore_LayoutStructure
#define FileCore_LayoutStructure                 0x00040548
#undef FileCore_MiscOp
#define FileCore_MiscOp                          0x00040549
#undef FileCore_SectorDiscOp
#define FileCore_SectorDiscOp                    0x0004054A
#undef FileCore_FreeSpace64
#define FileCore_FreeSpace64                     0x0004054B
#undef FileCore_DiscOp64
#define FileCore_DiscOp64                        0x0004054C
#undef FileCore_Features
#define FileCore_Features                        0x0004054D
#undef FilerAction_SendSelectedDirectory
#define FilerAction_SendSelectedDirectory        0x00040F80
#undef FilerAction_SendSelectedFile
#define FilerAction_SendSelectedFile             0x00040F81
#undef FilerAction_SendStartOperation
#define FilerAction_SendStartOperation           0x00040F82
#undef Filter_RegisterPreFilter
#define Filter_RegisterPreFilter                 0x00042640
#undef Filter_RegisterPostFilter
#define Filter_RegisterPostFilter                0x00042641
#undef Filter_DeRegisterPreFilter
#define Filter_DeRegisterPreFilter               0x00042642
#undef Filter_DeRegisterPostFilter
#define Filter_DeRegisterPostFilter              0x00042643
#undef Filter_RegisterRectFilter
#define Filter_RegisterRectFilter                0x00042644
#undef Filter_DeRegisterRectFilter
#define Filter_DeRegisterRectFilter              0x00042645
#undef Filter_RegisterCopyFilter
#define Filter_RegisterCopyFilter                0x00042646
#undef Filter_DeRegisterCopyFilter
#define Filter_DeRegisterCopyFilter              0x00042647
#undef Filter_RegisterPostRectFilter
#define Filter_RegisterPostRectFilter            0x00042648
#undef Filter_DeRegisterPostRectFilter
#define Filter_DeRegisterPostRectFilter          0x00042649
#undef Filter_RegisterPostIconFilter
#define Filter_RegisterPostIconFilter            0x0004264A
#undef Filter_DeRegisterPostIconFilter
#define Filter_DeRegisterPostIconFilter          0x0004264B
#undef Filter_RegisterIconBorderFilter
#define Filter_RegisterIconBorderFilter          0x0004264C
#undef Filter_DeRegisterIconBorderFilter
#define Filter_DeRegisterIconBorderFilter        0x0004264D
#undef Font_CacheAddr
#define Font_CacheAddr                           0x00040080 /*  &40080 */
#undef Font_FindFont
#define Font_FindFont                            0x00040081 /*  &40081 */
#undef Font_LoseFont
#define Font_LoseFont                            0x00040082 /*  &40082 */
#undef Font_ReadDefn
#define Font_ReadDefn                            0x00040083 /*  &40083 */
#undef Font_ReadInfo
#define Font_ReadInfo                            0x00040084 /*  &40084 */
#undef Font_StringWidth
#define Font_StringWidth                         0x00040085 /*  &40085 */
#undef Font_Paint
#define Font_Paint                               0x00040086 /*  &40086 */
#undef Font_Caret
#define Font_Caret                               0x00040087 /*  &40087 */
#undef Font_ConverttoOS
#define Font_ConverttoOS                         0x00040088 /*  &40088 */
#undef Font_Converttopoints
#define Font_Converttopoints                     0x00040089 /*  &40089 */
#undef Font_SetFont
#define Font_SetFont                             0x0004008A /*  &4008A */
#undef Font_CurrentFont
#define Font_CurrentFont                         0x0004008B /*  &4008B */
#undef Font_FutureFont
#define Font_FutureFont                          0x0004008C /*  &4008C */
#undef Font_FindCaret
#define Font_FindCaret                           0x0004008D /*  &4008D */
#undef Font_CharBBox
#define Font_CharBBox                            0x0004008E /*  &4008E */
#undef Font_ReadScaleFactor
#define Font_ReadScaleFactor                     0x0004008F /*  &4008F */
#undef Font_SetScaleFactor
#define Font_SetScaleFactor                      0x00040090 /*  &40090 */
#undef Font_ListFonts
#define Font_ListFonts                           0x00040091 /*  &40091 */
#undef Font_SetFontColours
#define Font_SetFontColours                      0x00040092 /*  &40092 */
#undef Font_SetPalette
#define Font_SetPalette                          0x00040093 /*  &40093 */
#undef Font_ReadThresholds
#define Font_ReadThresholds                      0x00040094 /*  &40094 */
#undef Font_SetThresholds
#define Font_SetThresholds                       0x00040095 /*  &40095 */
#undef Font_FindCaretJ
#define Font_FindCaretJ                          0x00040096 /*  &40096 */
#undef Font_StringBBox
#define Font_StringBBox                          0x00040097 /*  &40097 */
#undef Font_ReadColourTable
#define Font_ReadColourTable                     0x00040098 /*  &40098 */
#undef Font_MakeBitmap
#define Font_MakeBitmap                          0x00040099 /*  &40099 */
#undef Font_UnCacheFile
#define Font_UnCacheFile                         0x0004009A /*  &4009A */
#undef Font_SetFontMax
#define Font_SetFontMax                          0x0004009B /*  &4009B */
#undef Font_ReadFontMax
#define Font_ReadFontMax                         0x0004009C /*  &4009C */
#undef Font_ReadFontPrefix
#define Font_ReadFontPrefix                      0x0004009D /*  &4009D */
#undef Font_SwitchOutputToBuffer
#define Font_SwitchOutputToBuffer                0x0004009E /*  &4009E */
#undef Font_ReadFontMetrics
#define Font_ReadFontMetrics                     0x0004009F /*  &4009F */
#undef Font_DecodeMenu
#define Font_DecodeMenu                          0x000400A0 /*  &400A0 */
#undef Font_ScanString
#define Font_ScanString                          0x000400A1 /*  &400A1 */
#undef Font_SetColourTable
#define Font_SetColourTable                      0x000400A2 /*  &400A2 */
#undef Font_CurrentRGB
#define Font_CurrentRGB                          0x000400A3 /*  &400A3 */
#undef Font_FutureRGB
#define Font_FutureRGB                           0x000400A4 /*  &400A4 */
#undef Font_ReadEncodingFilename
#define Font_ReadEncodingFilename                0x000400A5 /*  &400A5 */
#undef Font_FindField
#define Font_FindField                           0x000400A6 /*  &400A6 */
#undef Font_ApplyFields
#define Font_ApplyFields                         0x000400A7 /*  &400A7 */
#undef Font_LookupFont
#define Font_LookupFont                          0x000400A8 /*  &400A8 */
#undef Font_ChangeArea
#define Font_ChangeArea                          0x000400BF /*  +63  -  for OS_ChangeDynamicArea */
#undef FPEmulator_Version
#define FPEmulator_Version                       &var_lookup("Module_SWISystemBase") + &var_lookup("FPEmulatorSWI") * &var_lookup("Module_SWIChunkSize") /*  &40480 */
#undef FPEmulator_DeactivateContext
#define FPEmulator_DeactivateContext             0x00000001
#undef FPEmulator_ActivateContext
#define FPEmulator_ActivateContext               0x00000002
#undef FPEmulator_ChangeContext
#define FPEmulator_ChangeContext                 0x00000003
#undef FPEmulator_ContextLength
#define FPEmulator_ContextLength                 0x00000004
#undef FPEmulator_InitContext
#define FPEmulator_InitContext                   0x00000005
#undef Free_Register
#define Free_Register                            0x000444C0 /*  &444C0 */
#undef Free_DeRegister
#define Free_DeRegister                          0x000444C1 /*  &444C1 */
#undef FSLock_Version
#define FSLock_Version                           0x00044780
#undef FSLock_Status
#define FSLock_Status                            0x00044781
#undef FSLock_ChangeStatus
#define FSLock_ChangeStatus                      0x00044782
#undef Hourglass_On
#define Hourglass_On                             0x000406C0
#undef Hourglass_Off
#define Hourglass_Off                            0x000406C1
#undef Hourglass_Smash
#define Hourglass_Smash                          0x000406C2
#undef Hourglass_Start
#define Hourglass_Start                          0x000406C3
#undef Hourglass_Percentage
#define Hourglass_Percentage                     0x000406C4
#undef Hourglass_LEDs
#define Hourglass_LEDs                           0x000406C5
#undef Hourglass_Colours
#define Hourglass_Colours                        0x000406C6
#undef HostFS_HostVdu
#define HostFS_HostVdu                           0x00040100
#undef HostFS_TubeVdu
#define HostFS_TubeVdu                           0x00040101
#undef HostFS_WriteC
#define HostFS_WriteC                            0x00040102
#undef IIC_Control
#define IIC_Control                              0x00000240 /*  +0 */
#undef MakePSFont_MakeFont
#define MakePSFont_MakeFont                      0x00043440 /*  &43440 */
#undef MessageTrans_FileInfo
#define MessageTrans_FileInfo                    0x00041500 /*  &41500 */
#undef MessageTrans_OpenFile
#define MessageTrans_OpenFile                    0x00041501 /*  &41501 */
#undef MessageTrans_Lookup
#define MessageTrans_Lookup                      0x00041502 /*  &41502 */
#undef MessageTrans_MakeMenus
#define MessageTrans_MakeMenus                   0x00041503 /*  &41503 */
#undef MessageTrans_CloseFile
#define MessageTrans_CloseFile                   0x00041504 /*  &41504 */
#undef MessageTrans_EnumerateTokens
#define MessageTrans_EnumerateTokens             0x00041505 /*  &41505 */
#undef MessageTrans_ErrorLookup
#define MessageTrans_ErrorLookup                 0x00041506 /*  &41506 */
#undef MessageTrans_GSLookup
#define MessageTrans_GSLookup                    0x00041507 /*  &41507 */
#undef MessageTrans_CopyError
#define MessageTrans_CopyError                   0x00041508 /*  &41508 */
#undef MessageTrans_Dictionary
#define MessageTrans_Dictionary                  0x00041509 /*  &41509 */
#undef OS_WriteC
#define OS_WriteC                                0x00000000 /*  &00 */
#undef OS_WriteS
#define OS_WriteS                                0x00000001 /*  &01 */
#undef OS_Write0
#define OS_Write0                                0x00000002 /*  &02 */
#undef OS_NewLine
#define OS_NewLine                               0x00000003 /*  &03 */
#undef OS_ReadC
#define OS_ReadC                                 0x00000004 /*  &04 */
#undef OS_CLI
#define OS_CLI                                   0x00000005 /*  &05 */
#undef OS_Byte
#define OS_Byte                                  0x00000006 /*  &06 */
#undef OS_Word
#define OS_Word                                  0x00000007 /*  &07 */
#undef OS_File
#define OS_File                                  0x00000008 /*  &08 */
#undef OS_Args
#define OS_Args                                  0x00000009 /*  &09 */
#undef OS_BGet
#define OS_BGet                                  0x0000000A /*  &0A */
#undef OS_BPut
#define OS_BPut                                  0x0000000B /*  &0B */
#undef OS_GBPB
#define OS_GBPB                                  0x0000000C /*  &0C */
#undef OS_Find
#define OS_Find                                  0x0000000D /*  &0D */
#undef OS_ReadLine
#define OS_ReadLine                              0x0000000E /*  &0E */
#undef OS_Control
#define OS_Control                               0x0000000F /*  &0F */
#undef OS_GetEnv
#define OS_GetEnv                                0x00000010 /*  &10 */
#undef OS_Exit
#define OS_Exit                                  0x00000011 /*  &11 */
#undef OS_SetEnv
#define OS_SetEnv                                0x00000012 /*  &12 */
#undef OS_IntOn
#define OS_IntOn                                 0x00000013 /*  &13 */
#undef OS_IntOff
#define OS_IntOff                                0x00000014 /*  &14 */
#undef OS_CallBack
#define OS_CallBack                              0x00000015 /*  &15 */
#undef OS_EnterOS
#define OS_EnterOS                               0x00000016 /*  &16 */
#undef OS_BreakPt
#define OS_BreakPt                               0x00000017 /*  &17 */
#undef OS_BreakCtrl
#define OS_BreakCtrl                             0x00000018 /*  &18 */
#undef OS_UnusedSWI
#define OS_UnusedSWI                             0x00000019 /*  &19 */
#undef OS_UpdateMEMC
#define OS_UpdateMEMC                            0x0000001A /*  &1A */
#undef OS_SetCallBack
#define OS_SetCallBack                           0x0000001B /*  &1B */
#undef OS_Mouse
#define OS_Mouse                                 0x0000001C /*  &1C */
#undef OS_Heap
#define OS_Heap                                  0x0000001D /*  &1D ; Our new ones start here */
#undef OS_Module
#define OS_Module                                0x0000001E /*  &1E */
#undef OS_Claim
#define OS_Claim                                 0x0000001F /*  &1F ; PMF's vector handling */
#undef OS_Release
#define OS_Release                               0x00000020 /*  &20 ; routines */
#undef OS_ReadUnsigned
#define OS_ReadUnsigned                          0x00000021 /*  &21 ; Read an unsigned number */
#undef OS_GenerateEvent
#define OS_GenerateEvent                         0x00000022 /*  &22 */
#undef OS_ReadVarVal
#define OS_ReadVarVal                            0x00000023 /*  &23 ; read variable value & type */
#undef OS_SetVarVal
#define OS_SetVarVal                             0x00000024 /*  &24 ; set  variable value & type */
#undef OS_GSInit
#define OS_GSInit                                0x00000025 /*  &25 */
#undef OS_GSRead
#define OS_GSRead                                0x00000026 /*  &26 */
#undef OS_GSTrans
#define OS_GSTrans                               0x00000027 /*  &27 */
#undef OS_BinaryToDecimal
#define OS_BinaryToDecimal                       0x00000028 /*  &28 */
#undef OS_FSControl
#define OS_FSControl                             0x00000029 /*  &29 */
#undef OS_ChangeDynamicArea
#define OS_ChangeDynamicArea                     0x0000002A /*  &2A */
#undef OS_GenerateError
#define OS_GenerateError                         0x0000002B /*  &2B */
#undef OS_ReadEscapeState
#define OS_ReadEscapeState                       0x0000002C /*  &2C */
#undef OS_EvaluateExpression
#define OS_EvaluateExpression                    0x0000002D /*  &2D */
#undef OS_SpriteOp
#define OS_SpriteOp                              0x0000002E /*  &2E */
#undef OS_ReadPalette
#define OS_ReadPalette                           0x0000002F /*  &2F ; (was FontManager) */
#undef OS_ServiceCall
#define OS_ServiceCall                           0x00000030 /*  &30 ; was Claim_Release_FIQ */
#undef OS_ReadVduVariables
#define OS_ReadVduVariables                      0x00000031 /*  &31 */
#undef OS_ReadPoint
#define OS_ReadPoint                             0x00000032 /*  &32 */
#undef OS_UpCall
#define OS_UpCall                                0x00000033 /*  &33 */
#undef OS_CallAVector
#define OS_CallAVector                           0x00000034 /*  &34 ; was ReadCurrentError */
#undef OS_ReadModeVariable
#define OS_ReadModeVariable                      0x00000035 /*  &35 */
#undef OS_RemoveCursors
#define OS_RemoveCursors                         0x00000036 /*  &36 */
#undef OS_RestoreCursors
#define OS_RestoreCursors                        0x00000037 /*  &37 */
#undef OS_SWINumberToString
#define OS_SWINumberToString                     0x00000038 /*  &38 */
#undef OS_SWINumberFromString
#define OS_SWINumberFromString                   0x00000039 /*  &39 */
#undef OS_ValidateAddress
#define OS_ValidateAddress                       0x0000003A /*  &3A */
#undef OS_CallAfter
#define OS_CallAfter                             0x0000003B /*  &3B */
#undef OS_CallEvery
#define OS_CallEvery                             0x0000003C /*  &3C */
#undef OS_RemoveTickerEvent
#define OS_RemoveTickerEvent                     0x0000003D /*  &3D */
#undef OS_InstallKeyHandler
#define OS_InstallKeyHandler                     0x0000003E /*  &3E */
#undef OS_CheckModeValid
#define OS_CheckModeValid                        0x0000003F /*  &3F */
#undef OS_ChangeEnvironment
#define OS_ChangeEnvironment                     0x00000040 /*  &40 */
#undef OS_ClaimScreenMemory
#define OS_ClaimScreenMemory                     0x00000041 /*  &41 */
#undef OS_ReadMonotonicTime
#define OS_ReadMonotonicTime                     0x00000042 /*  &42 */
#undef OS_SubstituteArgs
#define OS_SubstituteArgs                        0x00000043 /*  &43 */
#undef OS_PrettyPrint
#define OS_PrettyPrint                           0x00000044 /*  &44 */
#undef OS_Plot
#define OS_Plot                                  0x00000045 /*  &45 */
#undef OS_WriteN
#define OS_WriteN                                0x00000046 /*  &46 */
#undef OS_AddToVector
#define OS_AddToVector                           0x00000047 /*  &47 */
#undef OS_WriteEnv
#define OS_WriteEnv                              0x00000048 /*  &48 */
#undef OS_ReadArgs
#define OS_ReadArgs                              0x00000049 /*  &49 */
#undef OS_ReadRAMFsLimits
#define OS_ReadRAMFsLimits                       0x0000004A /*  &4A */
#undef OS_ClaimDeviceVector
#define OS_ClaimDeviceVector                     0x0000004B /*  &4B */
#undef OS_ReleaseDeviceVector
#define OS_ReleaseDeviceVector                   0x0000004C /*  &4C */
#undef OS_DelinkApplication
#define OS_DelinkApplication                     0x0000004D /*  &4D */
#undef OS_RelinkApplication
#define OS_RelinkApplication                     0x0000004E /*  &4E */
#undef OS_HeapSort
#define OS_HeapSort                              0x0000004F /*  &4F */
#undef OS_ExitAndDie
#define OS_ExitAndDie                            0x00000050 /*  &50 */
#undef OS_ReadMemMapInfo
#define OS_ReadMemMapInfo                        0x00000051 /*  &51 */
#undef OS_ReadMemMapEntries
#define OS_ReadMemMapEntries                     0x00000052 /*  &52 */
#undef OS_SetMemMapEntries
#define OS_SetMemMapEntries                      0x00000053 /*  &53 */
#undef OS_AddCallBack
#define OS_AddCallBack                           0x00000054 /*  &54 */
#undef OS_ReadDefaultHandler
#define OS_ReadDefaultHandler                    0x00000055 /*  &55 */
#undef OS_SetECFOrigin
#define OS_SetECFOrigin                          0x00000056 /*  &56 */
#undef OS_SerialOp
#define OS_SerialOp                              0x00000057 /*  &57 */
#undef OS_ReadSysInfo
#define OS_ReadSysInfo                           0x00000058 /*  &58 */
#undef OS_Confirm
#define OS_Confirm                               0x00000059 /*  &59 */
#undef OS_ChangedBox
#define OS_ChangedBox                            0x0000005A /*  &5A */
#undef OS_CRC
#define OS_CRC                                   0x0000005B /*  &5B */
#undef OS_ReadDynamicArea
#define OS_ReadDynamicArea                       0x0000005C /*  &5C */
#undef OS_PrintChar
#define OS_PrintChar                             0x0000005D /*  &5D */
#undef OS_ChangeRedirection
#define OS_ChangeRedirection                     0x0000005E /*  &5E */
#undef OS_RemoveCallBack
#define OS_RemoveCallBack                        0x0000005F /*  &5F */
#undef OS_FindMemMapEntries
#define OS_FindMemMapEntries                     0x00000060 /*  &60 */
#undef OS_SetColour
#define OS_SetColour                             0x00000061 /*  &61 */
#undef OS_ClaimSWI
#define OS_ClaimSWI                              0x00000062 /*  &62 ; In ToolkitSpt - Must be implemented */
#undef OS_ReleaseSWI
#define OS_ReleaseSWI                            0x00000063 /*  &63 ; OS > 3.10. */
#undef OS_Pointer
#define OS_Pointer                               0x00000064 /*  &64 */
#undef OS_ScreenMode
#define OS_ScreenMode                            0x00000065 /*  &65 */
#undef OS_DynamicArea
#define OS_DynamicArea                           0x00000066 /*  &66 */
#undef OS_AbortTrap
#define OS_AbortTrap                             0x00000067 /*  &67 */
#undef OS_Memory
#define OS_Memory                                0x00000068 /*  &68 */
#undef OS_ClaimProcessorVector
#define OS_ClaimProcessorVector                  0x00000069 /*  &69 */
#undef OS_Reset
#define OS_Reset                                 0x0000006A /*  &6A */
#undef OS_MMUControl
#define OS_MMUControl                            0x0000006B /*  &6B */
#undef OS_ResyncTime
#define OS_ResyncTime                            0x0000006C /*  &6C */
#undef OS_PlatformFeatures
#define OS_PlatformFeatures                      0x0000006D /*  &6D */
#undef OS_SynchroniseCodeAreas
#define OS_SynchroniseCodeAreas                  0x0000006E /*  &6E */
#undef OS_CallASWI
#define OS_CallASWI                              0x0000006F /*  &6F */
#undef OS_AMBControl
#define OS_AMBControl                            0x00000070 /*  &70 */
#undef OS_CallASWIR12
#define OS_CallASWIR12                           0x00000071 /*  &71 */
#undef OS_SpecialControl
#define OS_SpecialControl                        0x00000072 /*  &72 */
#undef OS_EnterUSR32
#define OS_EnterUSR32                            0x00000073 /*  &73 */
#undef OS_EnterUSR26
#define OS_EnterUSR26                            0x00000074 /*  &74 */
#undef OS_UKSWI75
#define OS_UKSWI75                               0x00000075 /*  &75 */
#undef OS_UKSWI76
#define OS_UKSWI76                               0x00000076 /*  &76 */
#undef OS_ClaimOSSWI
#define OS_ClaimOSSWI                            0x00000077 /*  &77 */
#undef OS_TaskControl
#define OS_TaskControl                           0x00000078 /*  &78 */
#undef OS_DeviceDriver
#define OS_DeviceDriver                          0x00000079 /*  &79 */
#undef OS_Hardware
#define OS_Hardware                              0x0000007A /*  &7A */
#undef OS_IICOp
#define OS_IICOp                                 0x0000007B /*  &7B */
#undef OS_LeaveOS
#define OS_LeaveOS                               0x0000007C /*  &7C */
#undef OS_ReadLine32
#define OS_ReadLine32                            0x0000007D /*  &7D */
#undef OS_SubstituteArgs32
#define OS_SubstituteArgs32                      0x0000007E /*  &7E */
#undef OS_HeapSort32
#define OS_HeapSort32                            0x0000007F /*  &7F */
#undef OS_ConvertStandardDateAndTime
#define OS_ConvertStandardDateAndTime            0x000000C0 /*  &C0 */
#undef OS_ConvertDateAndTime
#define OS_ConvertDateAndTime                    0x000000C1 /*  &C1 */
#undef OS_ConvertHex1
#define OS_ConvertHex1                           0x000000D0 /*  &D0 */
#undef OS_ConvertHex2
#define OS_ConvertHex2                           0x000000D1 /*  &D1 */
#undef OS_ConvertHex4
#define OS_ConvertHex4                           0x000000D2 /*  &D2 */
#undef OS_ConvertHex6
#define OS_ConvertHex6                           0x000000D3 /*  &D3 */
#undef OS_ConvertHex8
#define OS_ConvertHex8                           0x000000D4 /*  &D4 */
#undef OS_ConvertCardinal1
#define OS_ConvertCardinal1                      0x000000D5 /*  &D5 */
#undef OS_ConvertCardinal2
#define OS_ConvertCardinal2                      0x000000D6 /*  &D6 */
#undef OS_ConvertCardinal3
#define OS_ConvertCardinal3                      0x000000D7 /*  &D7 */
#undef OS_ConvertCardinal4
#define OS_ConvertCardinal4                      0x000000D8 /*  &D8 */
#undef OS_ConvertInteger1
#define OS_ConvertInteger1                       0x000000D9 /*  &D9 */
#undef OS_ConvertInteger2
#define OS_ConvertInteger2                       0x000000DA /*  &DA */
#undef OS_ConvertInteger3
#define OS_ConvertInteger3                       0x000000DB /*  &DB */
#undef OS_ConvertInteger4
#define OS_ConvertInteger4                       0x000000DC /*  &DC */
#undef OS_ConvertBinary1
#define OS_ConvertBinary1                        0x000000DD /*  &DD */
#undef OS_ConvertBinary2
#define OS_ConvertBinary2                        0x000000DE /*  &DE */
#undef OS_ConvertBinary3
#define OS_ConvertBinary3                        0x000000DF /*  &DF */
#undef OS_ConvertBinary4
#define OS_ConvertBinary4                        0x000000E0 /*  &E0 */
#undef OS_ConvertSpacedCardinal1
#define OS_ConvertSpacedCardinal1                0x000000E1 /*  &E1 */
#undef OS_ConvertSpacedCardinal2
#define OS_ConvertSpacedCardinal2                0x000000E2 /*  &E2 */
#undef OS_ConvertSpacedCardinal3
#define OS_ConvertSpacedCardinal3                0x000000E3 /*  &E3 */
#undef OS_ConvertSpacedCardinal4
#define OS_ConvertSpacedCardinal4                0x000000E4 /*  &E4 */
#undef OS_ConvertSpacedInteger1
#define OS_ConvertSpacedInteger1                 0x000000E5 /*  &E5 */
#undef OS_ConvertSpacedInteger2
#define OS_ConvertSpacedInteger2                 0x000000E6 /*  &E6 */
#undef OS_ConvertSpacedInteger3
#define OS_ConvertSpacedInteger3                 0x000000E7 /*  &E7 */
#undef OS_ConvertSpacedInteger4
#define OS_ConvertSpacedInteger4                 0x000000E8 /*  &E8 */
#undef OS_ConvertFixedNetStation
#define OS_ConvertFixedNetStation                0x000000E9 /*  &E9 */
#undef OS_ConvertNetStation
#define OS_ConvertNetStation                     0x000000EA /*  &EA */
#undef OS_ConvertFixedFileSize
#define OS_ConvertFixedFileSize                  0x000000EB /*  &EB */
#undef OS_ConvertFileSize
#define OS_ConvertFileSize                       0x000000EC /*  &EC */
#undef OS_WriteI
#define OS_WriteI                                0x00000100 /*  &100-&1FF */
#undef PDriver_Info
#define PDriver_Info                             0x00080140 /*  +0 */
#undef PDriver_SetInfo
#define PDriver_SetInfo                          0x00080141 /*  +1 */
#undef PDriver_CheckFeatures
#define PDriver_CheckFeatures                    0x00080142 /*  +2 */
#undef PDriver_PageSize
#define PDriver_PageSize                         0x00080143 /*  +3 */
#undef PDriver_SetPageSize
#define PDriver_SetPageSize                      0x00080144 /*  +4 */
#undef PDriver_SelectJob
#define PDriver_SelectJob                        0x00080145 /*  +5 */
#undef PDriver_CurrentJob
#define PDriver_CurrentJob                       0x00080146 /*  +6 */
#undef PDriver_FontSWI
#define PDriver_FontSWI                          0x00080147 /*  +7 */
#undef PDriver_EndJob
#define PDriver_EndJob                           0x00080148 /*  +8 */
#undef PDriver_AbortJob
#define PDriver_AbortJob                         0x00080149 /*  +9 */
#undef PDriver_Reset
#define PDriver_Reset                            0x0008014A /*  +10 */
#undef PDriver_GiveRectangle
#define PDriver_GiveRectangle                    0x0008014B /*  +11 */
#undef PDriver_DrawPage
#define PDriver_DrawPage                         0x0008014C /*  +12 */
#undef PDriver_GetRectangle
#define PDriver_GetRectangle                     0x0008014D /*  +13 */
#undef PDriver_CancelJob
#define PDriver_CancelJob                        0x0008014E /*  +14 */
#undef PDriver_ScreenDump
#define PDriver_ScreenDump                       0x0008014F /*  +15 */
#undef PDriver_EnumerateJobs
#define PDriver_EnumerateJobs                    0x00080150 /*  +16 */
#undef PDriver_SetPrinter
#define PDriver_SetPrinter                       0x00080151 /*  +17 */
#undef PDriver_CancelJobWithError
#define PDriver_CancelJobWithError               0x00080152 /*  +18 */
#undef PDriver_SelectIllustration
#define PDriver_SelectIllustration               0x00080153 /*  +19 */
#undef PDriver_InsertIllustration
#define PDriver_InsertIllustration               0x00080154 /*  +20 */
#undef PDriver_DeclareFont
#define PDriver_DeclareFont                      0x00080155 /*  +21 */
#undef PDriver_DeclareDriver
#define PDriver_DeclareDriver                    0x00080156 /*  +22 */
#undef PDriver_RemoveDriver
#define PDriver_RemoveDriver                     0x00080157 /*  +23 */
#undef PDriver_SelectDriver
#define PDriver_SelectDriver                     0x00080158 /*  +24 */
#undef PDriver_EnumerateDrivers
#define PDriver_EnumerateDrivers                 0x00080159 /*  +25 */
#undef PDriver_MiscOp
#define PDriver_MiscOp                           0x0008015A /*  +26 */
#undef PDriver_MiscOpForDriver
#define PDriver_MiscOpForDriver                  0x0008015B /*  +27 */
#undef PDriver_SetDriver
#define PDriver_SetDriver                        0x0008015C /*  +28 */
#undef PDriver_JPEGSWI
#define PDriver_JPEGSWI                          0x0008015D /*  +29 */
#undef PDumper_Info
#define PDumper_Info                             0x00041B00 /*  &41B00 */
#undef PDumper_Claim
#define PDumper_Claim                            0x00041B01 /*  &41B01 */
#undef PDumper_Free
#define PDumper_Free                             0x00041B02 /*  &41B02 */
#undef PDumper_Find
#define PDumper_Find                             0x00041B03 /*  &41B03 */
#undef PDumper_StartJob
#define PDumper_StartJob                         0x00041B04 /*  &41B04 */
#undef PDumper_TidyJob
#define PDumper_TidyJob                          0x00041B05 /*  &41B05 */
#undef PDumper_SetColour
#define PDumper_SetColour                        0x00041B06 /*  &41B06 */
#undef PDumper_PrepareStrip
#define PDumper_PrepareStrip                     0x00041B07 /*  &41B07 */
#undef PDumper_LookupError
#define PDumper_LookupError                      0x00041B08 /*  &41B08 */
#undef PDumper_CopyFilename
#define PDumper_CopyFilename                     0x00041B09 /*  &41B09 */
#undef Podule_ReadID
#define Podule_ReadID                            0x00040280
#undef Podule_ReadHeader
#define Podule_ReadHeader                        0x00040281
#undef Podule_EnumerateChunks
#define Podule_EnumerateChunks                   0x00040282
#undef Podule_ReadChunk
#define Podule_ReadChunk                         0x00040283
#undef Podule_ReadBytes
#define Podule_ReadBytes                         0x00040284
#undef Podule_WriteBytes
#define Podule_WriteBytes                        0x00040285
#undef Podule_CallLoader
#define Podule_CallLoader                        0x00040286
#undef Podule_RawRead
#define Podule_RawRead                           0x00040287
#undef Podule_RawWrite
#define Podule_RawWrite                          0x00040288
#undef Podule_HardwareAddress
#define Podule_HardwareAddress                   0x00040289
#undef Podule_EnumerateChunksWithInfo
#define Podule_EnumerateChunksWithInfo           0x0004028A
#undef Podule_HardwareAddresses
#define Podule_HardwareAddresses                 0x0004028B
#undef Podule_ReturnNumber
#define Podule_ReturnNumber                      0x0004028C
#undef Podule_ReadInfo
#define Podule_ReadInfo                          0x0004028D
#undef Podule_SetSpeed
#define Podule_SetSpeed                          0x0004028E
#undef Portable_Speed
#define Portable_Speed                           0x00042FC0 /*  &42FC0 */
#undef Portable_Control
#define Portable_Control                         0x00042FC1 /*  &42FC1 */
#undef Portable_ReadBMUVariable
#define Portable_ReadBMUVariable                 0x00042FC2 /*  &42FC2 */
#undef Portable_WriteBMUVariable
#define Portable_WriteBMUVariable                0x00042FC3 /*  &42FC3 */
#undef Portable_CommandBMU
#define Portable_CommandBMU                      0x00042FC4 /*  &42FC4 */
#undef Portable_ReadFeatures
#define Portable_ReadFeatures                    0x00042FC5 /*  &42FC5 */
#undef Portable_Idle
#define Portable_Idle                            0x00042FC6 /*  &42FC6 */
#undef Portable_Stop
#define Portable_Stop                            0x00042FC7 /*  &42FC7 */
#undef Portable_Status
#define Portable_Status                          0x00042FC8 /*  &42FC8 */
#undef RamFS_DiscOp
#define RamFS_DiscOp                             0x00040780 /*  &40780 */
#undef RamFS_NOP1
#define RamFS_NOP1                               0x00040781 /*  &40781 */
#undef RamFS_Drives
#define RamFS_Drives                             0x00040782 /*  &40782 */
#undef RamFS_FreeSpace
#define RamFS_FreeSpace                          0x00040783 /*  &40783 */
#undef RamFS_NOP2
#define RamFS_NOP2                               0x00040784 /*  &40784 */
#undef RamFS_DescribeDisc
#define RamFS_DescribeDisc                       0x00040785 /*  &40785 */
#undef ResourceFS_RegisterFiles
#define ResourceFS_RegisterFiles                 0x00041B40 /*  &41B40 */
#undef ResourceFS_DeregisterFiles
#define ResourceFS_DeregisterFiles               0x00041B41 /*  &41B41 */
#undef ScreenBlanker_Control
#define ScreenBlanker_Control                    0x00043100 /*  &43100 */
#undef ScreenModes_ReadInfo
#define ScreenModes_ReadInfo                     0x000487C0
#undef SCSI_Version
#define SCSI_Version                             0x000403C0 /*  +0   &403C0 */
#undef SCSI_Initialise
#define SCSI_Initialise                          0x000403C1 /*  +1   &403C1 */
#undef SCSI_Control
#define SCSI_Control                             0x000403C2 /*  +2   &403C2 */
#undef SCSI_Op
#define SCSI_Op                                  0x000403C3 /*  +3   &403C3 */
#undef SCSI_Status
#define SCSI_Status                              0x000403C4 /*  +4   &403C4 */
#undef SCSI_ReadControlLines
#define SCSI_ReadControlLines                    0x000403C5 /*  +5   &403C5  } Not supported by Acorn SCSIdriver */
#undef SCSI_EEProm
#define SCSI_EEProm                              0x000403C6 /*  +6   &403C6  } */
#undef SCSI_Reserve
#define SCSI_Reserve                             0x000403C7 /*  +7   &403C7 */
#undef SCSI_List
#define SCSI_List                                0x000403C8 /*  +8   &403C8 */
#undef SCSI_TargetControl
#define SCSI_TargetControl                       0x000403C9 /*  +9   &403C9  } Not supported by Acorn SCSIDriver */
#undef SCSI_LogVersion
#define SCSI_LogVersion                          0x00041080
#undef SCSI_LogList
#define SCSI_LogList                             0x00041081
#undef SCSIFS_DiscOp
#define SCSIFS_DiscOp                            0x00040980 /*  &40980 */
#undef SCSIFS_NOP1
#define SCSIFS_NOP1                              0x00040981 /*  &40981 */
#undef SCSIFS_Drives
#define SCSIFS_Drives                            0x00040982 /*  &40982 */
#undef SCSIFS_FreeSpace
#define SCSIFS_FreeSpace                         0x00040983 /*  &40983 */
#undef SCSIFS_NOP2
#define SCSIFS_NOP2                              0x00040984 /*  &40984 */
#undef SCSIFS_DescribeDisc
#define SCSIFS_DescribeDisc                      0x00040985 /*  &40985 */
#undef SCSIFS_TestReady
#define SCSIFS_TestReady                         0x00040986 /*  &40986 */
#undef SCSIFS_NOP3
#define SCSIFS_NOP3                              0x00040987 /*  &40987  */
#undef SCSIFS_NOP4
#define SCSIFS_NOP4                              0x00040988 /*  &40988  */
#undef SCSIFS_NOP5
#define SCSIFS_NOP5                              0x00040989 /*  &40989  */
#undef SCSIFS_NOP6
#define SCSIFS_NOP6                              0x0004098A /*  &4098a  */
#undef SCSIFS_NOP7
#define SCSIFS_NOP7                              0x0004098B /*  &4098b  */
#undef SCSIFS_MiscOp
#define SCSIFS_MiscOp                            0x0004098C /*  &4098c  */
#undef SCSIFS_SectorDiscOp
#define SCSIFS_SectorDiscOp                      0x0004098D /*  &4098d */
#undef SCSIFS_NOP8
#define SCSIFS_NOP8                              0x0004098E /*  &4098e */
#undef SCSIFS_NOP9
#define SCSIFS_NOP9                              0x0004098F /*  &4098f */
#undef SCSIFS_NOP10
#define SCSIFS_NOP10                             0x00040990 /*  &40990 */
#undef SCSIFS_NOP11
#define SCSIFS_NOP11                             0x00040991 /*  &40991 */
#undef SCSIFS_FreeSpace64
#define SCSIFS_FreeSpace64                       0x00040992 /*  &40992 */
#undef Shell_Create
#define Shell_Create                             0x000405C0
#undef Shell_Destroy
#define Shell_Destroy                            0x000405C1
#undef Sound_Configure
#define Sound_Configure                          0x00040140
#undef Sound_Enable
#define Sound_Enable                             0x00040141
#undef Sound_Stereo
#define Sound_Stereo                             0x00040142
#undef Sound_Speaker
#define Sound_Speaker                            0x00040143
#undef Sound_Mode
#define Sound_Mode                               0x00040144
#undef Sound_LinearHandler
#define Sound_LinearHandler                      0x00040145
#undef Sound_SampleRate
#define Sound_SampleRate                         0x00040146
#undef Sound_Volume
#define Sound_Volume                             0x00040180
#undef Sound_SoundLog
#define Sound_SoundLog                           0x00040181
#undef Sound_LogScale
#define Sound_LogScale                           0x00040182
#undef Sound_InstallVoice
#define Sound_InstallVoice                       0x00040183
#undef Sound_RemoveVoice
#define Sound_RemoveVoice                        0x00040184
#undef Sound_AttachVoice
#define Sound_AttachVoice                        0x00040185
#undef Sound_ControlPacked
#define Sound_ControlPacked                      0x00040186 /*  was 'Sound' but not in module! */
#undef Sound_Tuning
#define Sound_Tuning                             0x00040187
#undef Sound_Pitch
#define Sound_Pitch                              0x00040188
#undef Sound_Control
#define Sound_Control                            0x00040189
#undef Sound_AttachNamedVoice
#define Sound_AttachNamedVoice                   0x0004018A
#undef Sound_ReadControlBlock
#define Sound_ReadControlBlock                   0x0004018B
#undef Sound_WriteControlBlock
#define Sound_WriteControlBlock                  0x0004018C
#undef Sound_QInit
#define Sound_QInit                              0x000401C0
#undef Sound_QSchedule
#define Sound_QSchedule                          0x000401C1
#undef Sound_QRemove
#define Sound_QRemove                            0x000401C2
#undef Sound_QFree
#define Sound_QFree                              0x000401C3
#undef Sound_QSDispatch
#define Sound_QSDispatch                         0x000401C4
#undef Sound_QTempo
#define Sound_QTempo                             0x000401C5
#undef Sound_QBeat
#define Sound_QBeat                              0x000401C6
#undef Sound_QInterface
#define Sound_QInterface                         0x000401C7
#undef Squash_Compress
#define Squash_Compress                          0x00042700
#undef Squash_Decompress
#define Squash_Decompress                        0x00042701
#undef Super_Sample90
#define Super_Sample90                           0x00040D80 /*  &40D80  internal use only (by Font Manager) */
#undef Super_Sample45
#define Super_Sample45                           0x00040D81 /*  &40D81  internal use only (by Font Manager) */
#undef TaskManager_TaskNameFromHandle
#define TaskManager_TaskNameFromHandle           0x00042680
#undef TaskManager_EnumerateTasks
#define TaskManager_EnumerateTasks               0x00042681
#undef TaskManager_Shutdown
#define TaskManager_Shutdown                     0x00042682 /*  Switcher 0.60 onwards */
#undef TaskManager_StartTask
#define TaskManager_StartTask                    0x00042683
#undef TaskWindow_TaskInfo
#define TaskWindow_TaskInfo                      0x00043380 /*  43380 */
#undef Territory_Number
#define Territory_Number                         0x00043040
#undef Territory_Register
#define Territory_Register                       0x00043041
#undef Territory_Deregister
#define Territory_Deregister                     0x00043042
#undef Territory_NumberToName
#define Territory_NumberToName                   0x00043043
#undef Territory_Exists
#define Territory_Exists                         0x00043044
#undef Territory_AlphabetNumberToName
#define Territory_AlphabetNumberToName           0x00043045
#undef Territory_SelectAlphabet
#define Territory_SelectAlphabet                 0x00043046
#undef Territory_SetTime
#define Territory_SetTime                        0x00043047
#undef Territory_ReadCurrentTimeZone
#define Territory_ReadCurrentTimeZone            0x00043048
#undef Territory_ConvertTimeToUTCOrdinals
#define Territory_ConvertTimeToUTCOrdinals       0x00043049
#undef Territory_ReadTimeZones
#define Territory_ReadTimeZones                  0x0004304A
#undef Territory_ConvertDateAndTime
#define Territory_ConvertDateAndTime             0x0004304B
#undef Territory_ConvertStandardDateAndTime
#define Territory_ConvertStandardDateAndTime     0x0004304C
#undef Territory_ConvertStandardDate
#define Territory_ConvertStandardDate            0x0004304D
#undef Territory_ConvertStandardTime
#define Territory_ConvertStandardTime            0x0004304E
#undef Territory_ConvertTimeToOrdinals
#define Territory_ConvertTimeToOrdinals          0x0004304F
#undef Territory_ConvertTimeStringToOrdinals
#define Territory_ConvertTimeStringToOrdinals    0x00043050
#undef Territory_ConvertOrdinalsToTime
#define Territory_ConvertOrdinalsToTime          0x00043051
#undef Territory_Alphabet
#define Territory_Alphabet                       0x00043052
#undef Territory_AlphabetIdentifier
#define Territory_AlphabetIdentifier             0x00043053
#undef Territory_SelectKeyboardHandler
#define Territory_SelectKeyboardHandler          0x00043054
#undef Territory_WriteDirection
#define Territory_WriteDirection                 0x00043055
#undef Territory_CharacterPropertyTable
#define Territory_CharacterPropertyTable         0x00043056
#undef Territory_LowerCaseTable
#define Territory_LowerCaseTable                 0x00043057
#undef Territory_UpperCaseTable
#define Territory_UpperCaseTable                 0x00043058
#undef Territory_ControlTable
#define Territory_ControlTable                   0x00043059
#undef Territory_PlainTable
#define Territory_PlainTable                     0x0004305A
#undef Territory_ValueTable
#define Territory_ValueTable                     0x0004305B
#undef Territory_RepresentationTable
#define Territory_RepresentationTable            0x0004305C
#undef Territory_Collate
#define Territory_Collate                        0x0004305D
#undef Territory_ReadSymbols
#define Territory_ReadSymbols                    0x0004305E
#undef Territory_ReadCalendarInformation
#define Territory_ReadCalendarInformation        0x0004305F
#undef Territory_NameToNumber
#define Territory_NameToNumber                   0x00043060
#undef Territory_TransformString
#define Territory_TransformString                0x00043061 /*  &43061 */
#undef Territory_ConvertTextToString
#define Territory_ConvertTextToString            0x00043075 /*  &43075 */
#undef Wimp_Initialise
#define Wimp_Initialise                          0x000400C0 /*  &400C0 */
#undef Wimp_CreateWindow
#define Wimp_CreateWindow                        0x000400C1 /*  &400C1 */
#undef Wimp_CreateIcon
#define Wimp_CreateIcon                          0x000400C2 /*  &400C2 */
#undef Wimp_DeleteWindow
#define Wimp_DeleteWindow                        0x000400C3 /*  &400C3 */
#undef Wimp_DeleteIcon
#define Wimp_DeleteIcon                          0x000400C4 /*  &400C4 */
#undef Wimp_OpenWindow
#define Wimp_OpenWindow                          0x000400C5 /*  &400C5 */
#undef Wimp_CloseWindow
#define Wimp_CloseWindow                         0x000400C6 /*  &400C6 */
#undef Wimp_Poll
#define Wimp_Poll                                0x000400C7 /*  &400C7 */
#undef Wimp_RedrawWindow
#define Wimp_RedrawWindow                        0x000400C8 /*  &400C8 */
#undef Wimp_UpdateWindow
#define Wimp_UpdateWindow                        0x000400C9 /*  &400C9 */
#undef Wimp_GetRectangle
#define Wimp_GetRectangle                        0x000400CA /*  &400CA */
#undef Wimp_GetWindowState
#define Wimp_GetWindowState                      0x000400CB /*  &400CB */
#undef Wimp_GetWindowInfo
#define Wimp_GetWindowInfo                       0x000400CC /*  &400CC */
#undef Wimp_SetIconState
#define Wimp_SetIconState                        0x000400CD /*  &400CD */
#undef Wimp_GetIconState
#define Wimp_GetIconState                        0x000400CE /*  &400CE */
#undef Wimp_GetPointerInfo
#define Wimp_GetPointerInfo                      0x000400CF /*  &400CF */
#undef Wimp_DragBox
#define Wimp_DragBox                             0x000400D0 /*  &400D0 */
#undef Wimp_ForceRedraw
#define Wimp_ForceRedraw                         0x000400D1 /*  &400D1 */
#undef Wimp_SetCaretPosition
#define Wimp_SetCaretPosition                    0x000400D2 /*  &400D2 */
#undef Wimp_GetCaretPosition
#define Wimp_GetCaretPosition                    0x000400D3 /*  &400D3 */
#undef Wimp_CreateMenu
#define Wimp_CreateMenu                          0x000400D4 /*  &400D4 */
#undef Wimp_DecodeMenu
#define Wimp_DecodeMenu                          0x000400D5 /*  &400D5 */
#undef Wimp_WhichIcon
#define Wimp_WhichIcon                           0x000400D6 /*  &400D6 */
#undef Wimp_SetExtent
#define Wimp_SetExtent                           0x000400D7 /*  &400D7 */
#undef Wimp_SetPointerShape
#define Wimp_SetPointerShape                     0x000400D8 /*  &400D8 */
#undef Wimp_OpenTemplate
#define Wimp_OpenTemplate                        0x000400D9 /*  &400D9 */
#undef Wimp_CloseTemplate
#define Wimp_CloseTemplate                       0x000400DA /*  &400DA */
#undef Wimp_LoadTemplate
#define Wimp_LoadTemplate                        0x000400DB /*  &400DB */
#undef Wimp_ProcessKey
#define Wimp_ProcessKey                          0x000400DC /*  &400DC */
#undef Wimp_CloseDown
#define Wimp_CloseDown                           0x000400DD /*  &400DD */
#undef Wimp_StartTask
#define Wimp_StartTask                           0x000400DE /*  &400DE */
#undef Wimp_ReportError
#define Wimp_ReportError                         0x000400DF /*  &400DF */
#undef Wimp_GetWindowOutline
#define Wimp_GetWindowOutline                    0x000400E0 /*  &400E0 */
#undef Wimp_PollIdle
#define Wimp_PollIdle                            0x000400E1 /*  &400E1 */
#undef Wimp_PlotIcon
#define Wimp_PlotIcon                            0x000400E2 /*  &400E2 */
#undef Wimp_SetMode
#define Wimp_SetMode                             0x000400E3 /*  &400E3 */
#undef Wimp_SetPalette
#define Wimp_SetPalette                          0x000400E4 /*  &400E4 */
#undef Wimp_ReadPalette
#define Wimp_ReadPalette                         0x000400E5 /*  &400E5 */
#undef Wimp_SetColour
#define Wimp_SetColour                           0x000400E6 /*  &400E6 */
#undef Wimp_SendMessage
#define Wimp_SendMessage                         0x000400E7 /*  &400E7 */
#undef Wimp_CreateSubMenu
#define Wimp_CreateSubMenu                       0x000400E8 /*  &400E8 */
#undef Wimp_SpriteOp
#define Wimp_SpriteOp                            0x000400E9 /*  &400E9 */
#undef Wimp_BaseOfSprites
#define Wimp_BaseOfSprites                       0x000400EA /*  &400EA */
#undef Wimp_BlockCopy
#define Wimp_BlockCopy                           0x000400EB /*  &400EB */
#undef Wimp_SlotSize
#define Wimp_SlotSize                            0x000400EC /*  &400EC */
#undef Wimp_ReadPixTrans
#define Wimp_ReadPixTrans                        0x000400ED /*  &400ED */
#undef Wimp_ClaimFreeMemory
#define Wimp_ClaimFreeMemory                     0x000400EE /*  &400EE */
#undef Wimp_CommandWindow
#define Wimp_CommandWindow                       0x000400EF /*  &400EF */
#undef Wimp_TextColour
#define Wimp_TextColour                          0x000400F0 /*  &400F0 */
#undef Wimp_TransferBlock
#define Wimp_TransferBlock                       0x000400F1 /*  &400F1 */
#undef Wimp_ReadSysInfo
#define Wimp_ReadSysInfo                         0x000400F2 /*  &400F2 */
#undef Wimp_SetFontColours
#define Wimp_SetFontColours                      0x000400F3 /*  &400F3 */
#undef Wimp_GetMenuState
#define Wimp_GetMenuState                        0x000400F4 /*  &400F4        Wimp 2.18 onwards */
#undef Wimp_RegisterFilter
#define Wimp_RegisterFilter                      0x000400F5 /*  &400F5        Wimp 2.85 onwards */
#undef Wimp_AddMessages
#define Wimp_AddMessages                         0x000400F6 /*  &400F6        Wimp 2.95 onwards */
#undef Wimp_RemoveMessages
#define Wimp_RemoveMessages                      0x000400F7 /*  &400F7        Wimp 3.05 onwards */
#undef Wimp_SetColourMapping
#define Wimp_SetColourMapping                    0x000400F8 /*  &400F8 */
#undef Wimp_TextOp
#define Wimp_TextOp                              0x000400F9 /*  &400F9        Wimp 3.23 onwards */
#undef Wimp_SetWatchdogState
#define Wimp_SetWatchdogState                    0x000400FA /*  &400FA        Wimp 3.22 onwards */
#undef Wimp_Extend
#define Wimp_Extend                              0x000400FB /*  &400FB */
#undef Wimp_ResizeIcon
#define Wimp_ResizeIcon                          0x000400FC /*  &400FC */
#undef Wimp_AutoScroll
#define Wimp_AutoScroll                          0x000400FD /*  &400FD        Wimp 4.00 onwards */

#endif
