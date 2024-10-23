#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Runtime/BeamRuntime.h"

#include "K2BeamNode_Operation_Auth.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FrictionlessAuth"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FrictionlessAuth : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Frictionless Authentication"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LoginFrictionlessOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_LoginEmailAndPassword"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_LoginEmailAndPassword : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - Email and Password"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LoginEmailAndPasswordOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_LoginExternalIdentity"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_LoginExternalIdentity : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - External Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LoginExternalIdentityOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_SignUpEmailAndPassword"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_SignUpEmailAndPassword : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - SignUp - Email and Password"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SignUpEmailAndPasswordOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_SignUpExternalIdentity"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_SignUpExternalIdentity : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - SignUp - External Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SignUpExternalIdentityOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_AttachEmailAndPassword"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_AttachEmailAndPassword : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Attach - Email and Password"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, AttachEmailAndPasswordOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_AttachExternalIdentity"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_AttachExternalIdentity : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Attach - External Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, AttachExternalIdentityOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_Logout"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_Logout : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Logout"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LogoutOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ManuallyInitializeSubsystemWithUserData"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_ManuallyInitializeSubsystemWithUserData : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Manually Initialize Subsystem With User Data"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, ManuallyInitializeSubsystemOperationWithUserData); }

	virtual TArray<FName> GetOperationEventIds(EBeamOperationEventType Type) const override
	{
		TArray<FName> Ids = Super::GetOperationEventIds(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add( UBeamRuntime::GetOperationEventID_SubsystemsInitializedWithoutUserData());
			return Ids;
		}

		return Ids;
	};

	virtual TArray<FString> GetOperationEventIdTooltips(EBeamOperationEventType Type) const override
	{
		TArray<FString> Ids = Super::GetOperationEventIdTooltips(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add(TEXT("Triggered when subsystems are initialized but did not initialize the user data till now"));
			return Ids;
		}
		return Ids;
	}
	
	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ManuallyInitializeSubsystem"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_ManuallyInitializeSubsystem : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Manually Initialize Subsystems WITHOUT User Data"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, ManuallyInitializeSubsystemOperation); }
	
	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
