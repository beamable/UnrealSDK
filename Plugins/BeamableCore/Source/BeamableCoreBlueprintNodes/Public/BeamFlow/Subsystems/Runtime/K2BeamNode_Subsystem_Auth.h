#pragma once

#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
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

#define LOCTEXT_NAMESPACE "UK2BeamNode_EventUnregisterAll_Auth"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_Auth : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Auth - Unbind All Events"); }

	virtual FString GetServiceName() const override { return "Auth"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

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

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetExternalIdentity"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetExternalIdentity : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Account - Try Get External Identity"); }

	virtual FString GetServiceName() const override { return "Account"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, TryGetExternalIdentity); }

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

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetSlotUserData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetSlotUserData : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Account - Try Get Slot User Data"); }

	virtual FString GetServiceName() const override { return "Account"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, TryGetSlotUserData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetSlotGamerTag"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetSlotGamerTag : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Account - Try Get Slot GamerTag"); }

	virtual FString GetServiceName() const override { return "Account"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, TryGetSlotGamerTag); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_LoginFromCache"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_LoginFromCache : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - Local Cache"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LoginFromCacheOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_LoginFrictionless"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_LoginFrictionless : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - Frictionless"); }

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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_LoginFederated"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_LoginFederated : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - Federated Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, LoginFederatedOperation); }


	virtual TArray<FName> GetOperationEventIds(EBeamOperationEventType Type) const override
	{
		TArray<FName> Ids = Super::GetOperationEventIds(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add(UBeamRuntime::GetOperationEventID_MultiFactorAuthTriggered());
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
			Ids.Add(TEXT("Triggered when you have a two factor auth, if it is not the case it will only goes for the regular flow."));
			return Ids;
		}
		return Ids;
	}

	virtual TMap<FName, UClass*> GetOperationEventCastClass(EBeamOperationEventType Type) const override
	{
		TMap<FName, UClass*> Casts = Super::GetOperationEventCastClass(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Casts.Add(UBeamRuntime::GetOperationEventID_MultiFactorAuthTriggered(), UBeamMultiFactorLoginData::StaticClass());
			return Casts;
		}
		return Casts;
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchExternalIdentityOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchExternalIdentityOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Identity - FetchExternalIdentityOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, FetchExternalIdentityOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CommitLoginFederated"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CommitLoginFederated : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Login - Commit Federated Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, CommitLoginFederatedOperation); }

private:
	virtual TArray<FName> GetOperationEventIds(EBeamOperationEventType Type) const override
	{
		TArray<FName> Ids = Super::GetOperationEventIds(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add(UBeamRuntime::GetOperationEventID_MultiFactorAuthTriggered());
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
			Ids.Add(TEXT("Triggered when the microservice federation sent back the challenge"));
			return Ids;
		}
		return Ids;
	}


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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_SignUpFederated"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_SignUpFederated : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - SignUp - Federated Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, SignUpFederatedOperation); }

	virtual TArray<FName> GetOperationEventIds(EBeamOperationEventType Type) const override
	{
		TArray<FName> Ids = Super::GetOperationEventIds(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add(UBeamRuntime::GetOperationEventID_MultiFactorAuthTriggered());
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
			Ids.Add(TEXT("Triggered when the microservice federation sent back the challenge"));
			return Ids;
		}
		return Ids;
	}

	virtual TMap<FName, UClass*> GetOperationEventCastClass(EBeamOperationEventType Type) const override
	{
		TMap<FName, UClass*> Casts = Super::GetOperationEventCastClass(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Casts.Add(UBeamRuntime::GetOperationEventID_MultiFactorAuthTriggered(), UBeamMultiFactorLoginData::StaticClass());
			return Casts;
		}
		return Casts;
	}

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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_AttachFederated"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_AttachFederated : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Attach - Federated Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, AttachFederatedOperation); }


	virtual TArray<FName> GetOperationEventIds(EBeamOperationEventType Type) const override
	{
		TArray<FName> Ids = Super::GetOperationEventIds(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add(UBeamRuntime::GetOperationEventID_MultiFactorAuthTriggered());
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
			Ids.Add(TEXT("Triggered when the microservice federation sent back the challenge"));
			return Ids;
		}
		return Ids;
	}

	virtual TMap<FName, UClass*> GetOperationEventCastClass(EBeamOperationEventType Type) const override
	{
		TMap<FName, UClass*> Casts = Super::GetOperationEventCastClass(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Casts.Add(UBeamRuntime::GetOperationEventID_MultiFactorAuthTriggered(), UBeamMultiFactorLoginData::StaticClass());
			return Casts;
		}
		return Casts;
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamRuntime::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CommitAttachFederatedOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CommitAttachFederatedOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Attach - Commit Federated Identity"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamRuntime, CommitAttachFederatedOperation); }

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
