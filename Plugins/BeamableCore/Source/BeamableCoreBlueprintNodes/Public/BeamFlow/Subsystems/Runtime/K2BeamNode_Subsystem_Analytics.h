#pragma once

#include "Runtime/BeamRuntime.h"
#include "BeamFlow/K2BeamNode_Analytics.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"

#include "K2BeamNode_Subsystem_Analytics.generated.h"

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_Analytics_SendAnalyticsEvent"

UCLASS(meta=(BeamAnalytics))
class UK2BeamNode_Analytics_SendAnalyticsEvent : public UK2BeamNode_Analytics
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Analytics - Send Analytics Event"); }

	virtual FString GetServiceName() const override { return "Analytics"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SendAnalyticsEventBeamSerializableUObject); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Analytics_SendAnalyticsEventSlot"

UCLASS(meta=(BeamAnalytics))
class UK2BeamNode_Analytics_SendAnalyticsEventSlot : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Analytics - Send Analytics Event User Slot"); }

	virtual FString GetServiceName() const override { return "Analytics"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SendAnalyticsEventForSlotBeamSerializableUObject); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Analytics_SendAnalyticsEventString"

UCLASS(meta=(BeamAnalytics))
class UK2BeamNode_Analytics_SendAnalyticsEventString : public UK2BeamNode_Analytics
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Analytics - Send Analytics Event (String)"); }

	virtual FString GetServiceName() const override { return "Analytics"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SendAnalyticsEventStringParams); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Analytics_SendAnalyticsEventSlotString"

UCLASS(meta=(BeamAnalytics))
class UK2BeamNode_Analytics_SendAnalyticsEventSlotString : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Analytics - Send Analytics Event (String) User Slot"); }

	virtual FString GetServiceName() const override { return "Analytics"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SendAnalyticsEventSlotStringParams); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
