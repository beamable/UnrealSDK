#pragma once

#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Runtime/BeamRuntime.h"

#include "K2BeamNode_Subsystem_Auth.generated.h"

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

#define LOCTEXT_NAMESPACE "UK2BeamNode_EventUnregister_Auth"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_Auth : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Auth - Unbind"); }

	virtual FString GetServiceName() const override { return "Auth"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_EventRegister_Auth"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_Auth : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Auth - Bind"); }

	virtual FString GetServiceName() const override { return "Auth"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_GetOwnerSlotConnectivity"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_GetOwnerSlotConnectivity : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Auth - GetOwnerSlotConnectivity"); }

	virtual FString GetServiceName() const override { return "Auth"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetOwnerSlotConnectivity); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_GetSlotConnectivity"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_GetSlotConnectivity : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Auth - GetSlotConnectivity"); }

	virtual FString GetServiceName() const override { return "Auth"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSlotConnectivity); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsInitialized"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsInitialized : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Auth - IsInitialized"); }

	virtual FString GetServiceName() const override { return "Auth"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, IsInitialized); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsLoggedIn"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsLoggedIn : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Auth - IsLoggedIn"); }

	virtual FString GetServiceName() const override { return "Auth"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, IsLoggedIn); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FrictionlessAuth"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FrictionlessAuth : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Frictionless Authentication"); }

	virtual FString GetServiceName() const override { return "Auth"; };

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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_BeginLoginExternalIdentityTwoFactorOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_BeginLoginExternalIdentityTwoFactorOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - BeginLoginExternalIdentityTwoFactorOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, BeginLoginExternalIdentityTwoFactorOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CommitLoginExternalIdentityTwoFactorOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CommitLoginExternalIdentityTwoFactorOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - CommitLoginExternalIdentityTwoFactorOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, CommitLoginExternalIdentityTwoFactorOperation); }

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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_BeginAttachExternalIdentityOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_BeginAttachExternalIdentityOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - BeginAttachExternalIdentityOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, BeginAttachExternalIdentityOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CommitAttachExternalIdentityOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CommitAttachExternalIdentityOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - CommitAttachExternalIdentityOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, CommitAttachExternalIdentityOperation); }

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
			Ids.Add(UBeamRuntime::GetOperationEventID_SubsystemsInitializedWithoutUserData());
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
