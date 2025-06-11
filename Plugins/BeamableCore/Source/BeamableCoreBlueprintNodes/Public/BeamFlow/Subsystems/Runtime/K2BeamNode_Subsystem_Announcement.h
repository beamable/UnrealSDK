#pragma once

#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
#include "BeamFlow/K2BeamNode_GetLocalStateForeach.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/LiveOps/BeamAnnouncementsSubsystem.h"
#include "K2BeamNode_Subsystem_Announcement.generated.h"

/***
 *      ______                          _         
 *     |  ____|                        | |        
 *     | |__    __   __   ___   _ __   | |_   ___ 
 *     |  __|   \ \ / /  / _ \ | '_ \  | __| / __|
 *     | |____   \ V /  |  __/ | | | | | |_  \__ \
 *     |______|   \_/    \___| |_| |_|  \__| |___/
 *                                                
 *                                                
 */

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregisterAll_AnnouncementsSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_AnnouncementsSubsystem : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Announcements - Unbind All Events"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregister_AnnouncementsSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_AnnouncementsSubsystem : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Announcements - Unbind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventRegister_AnnouncementsSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_AnnouncementsSubsystem : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Announcements - Bind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_GetAnnouncements"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_GetAnnouncements : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Announcement - GetAnnouncements"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetAnnouncements); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_MarkAnnouncementRead"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_MarkSingleAnnouncementRead : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Announcement - Mark Single Announcement Read"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, MarkSingleAnnouncementReadOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ModifyCurrencies"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_MarkGroupAnnouncementsRead : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Announcement - Mark group of Announcements as Read"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, MarkAnnouncementsReadOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ClaimAnnouncement"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_ClaimSingleAnnouncement : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Announcement - Claim Single Announcement Gift"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, ClaimSingleAnnouncementOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ClaimAnnouncements"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_ClaimGroupAnnouncements : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Announcement - Claim Group Of Announcements Gifts"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsSubsystem, ClaimAnnouncementsOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamAnnouncementsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
