// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_GetLocalStateForeach.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Lobby/BeamLobbySubsystem.h"

#include "K2BeamNode_Subsystem_Lobby.generated.h"


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


#define LOCTEXT_NAMESPACE "K2BeamNode_EventRegister_LobbySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_LobbySubsystem : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Lobby - Bind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregisterAll_LobbySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_LobbySubsystem : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Lobby - Unbind All Events"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregister_LobbySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_LobbySubsystem : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Lobby - Unbind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE


//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_GetCurrentLobby"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_GetCurrentLobby : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - GetCurrentLobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetCurrentLobby); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_GetCurrentSlotLobbyState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_GetCurrentSlotLobbyState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - GetCurrentSlotLobbyState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetCurrentSlotLobbyState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetLobbyById"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetLobbyById : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetLobbyById"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetLobbyById); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetCurrentLobby"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetCurrentLobby : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetCurrentLobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetCurrentLobby); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetGlobalLobbyData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetGlobalLobbyData : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetGlobalLobbyData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetGlobalLobbyData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_GetAllLobbyGlobalData"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_GetAllLobbyGlobalData : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - GetAllLobbyGlobalData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetAllLobbyGlobalData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetLobbyPlayerData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetLobbyPlayerData : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetLobbyPlayerData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetLobbyPlayerData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_GetAllLobbyPlayerData"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_GetAllLobbyPlayerData : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - GetAllLobbyPlayerData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetAllLobbyPlayerData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetGlobalLobbyDataById"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetGlobalLobbyDataById : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetGlobalLobbyDataById"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetGlobalLobbyDataById); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_GetAllLobbyGlobalDataById"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_GetAllLobbyGlobalDataById : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - GetAllLobbyGlobalDataById"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetAllLobbyGlobalDataById); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetLobbyPlayerDataById"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetLobbyPlayerDataById : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetLobbyPlayerDataById"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetLobbyPlayerDataById); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_GetAllLobbyPlayerDataById"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_GetAllLobbyPlayerDataById : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - GetAllLobbyPlayerDataById"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetAllLobbyPlayerDataById); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetCurrentLobbyState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetCurrentLobbyState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetCurrentLobbyState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetCurrentLobbyState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetDedicatedServerInstanceLobby"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetDedicatedServerInstanceLobby : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryGetDedicatedServerInstanceLobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryGetDedicatedServerInstanceLobby); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryBeginUpdateLobby"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryBeginUpdateLobby : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - TryBeginUpdateLobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, TryBeginUpdateLobby); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareUpdateName"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareUpdateName : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareUpdateName"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareUpdateName); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareUpdateDescription"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareUpdateDescription : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareUpdateDescription"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareUpdateDescription); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareUpdateRestriction"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareUpdateRestriction : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareUpdateRestriction"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareUpdateRestriction); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareUpdateGameType"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareUpdateGameType : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareUpdateGameType"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareUpdateGameType); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareUpdateHost"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareUpdateHost : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareUpdateHost"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareUpdateHost); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareUpdateMaxPlayers"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareUpdateMaxPlayers : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareUpdateMaxPlayers"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareUpdateMaxPlayers); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareUpdateGlobalData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareUpdateGlobalData : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareUpdateGlobalData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareUpdateGlobalData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_PrepareDeleteGlobalData"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_PrepareDeleteGlobalData : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Lobby - PrepareDeleteGlobalData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, PrepareDeleteGlobalData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_CreateOpenLobby"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_CreateOpenLobby : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Create Open Lobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, CreateOpenLobbyOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_CreateClosedLobby"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_CreateClosedLobby : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Create Closed Lobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, CreateClosedLobbyOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_RefreshLobbyData"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_RefreshLobbyData : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Refresh Lobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, RefreshLobbyDataOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_RefreshLobbiesData"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_RefreshLobbiesData : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Refresh Lobbies"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, RefreshLobbiesDataOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_JoinLobby"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_JoinLobby : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Join Lobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, JoinLobbyOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_JoinLobbyByPasscode"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_JoinLobbyByPasscode : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Join Lobby by Passcode"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, JoinLobbyByPasscodeOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_LeaveLobby"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_LeaveLobby : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Leave Lobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, LeaveLobbyOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_KickPlayer"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_KickPlayer : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Kick Player"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, KickPlayerOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_CommitLobbyUpdate"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_CommitLobbyUpdate : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Commit Lobby Update"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, CommitLobbyUpdateOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_UpdatePlayerData"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_UpdatePlayerData : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Update Player Data"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, UpdatePlayerDataOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_DeletePlayerData"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_DeletePlayerData : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Delete Player Data"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, DeletePlayerDataOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_DeleteSlotPlayerData"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_DeleteSlotPlayerData : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Delete Slot Player Data"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, DeleteSlotPlayerDataOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_ProvisionGameServerForLobby"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_ProvisionGameServerForLobby : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Lobby - Provision Game Server for Lobby"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLobbySubsystem, ProvisionGameServerForLobbyOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLobbySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
