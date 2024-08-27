#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/LiveOps/BeamAnnouncementsSubsystem.h"
#include "K2BeamNode_Operation_Announcement.generated.h"

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