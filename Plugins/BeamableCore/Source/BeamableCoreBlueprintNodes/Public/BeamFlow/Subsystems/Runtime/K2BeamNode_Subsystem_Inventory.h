#pragma once

#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_GetLocalStateForeach.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"

#include "K2BeamNode_Subsystem_Inventory.generated.h"

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

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregisterAll_InventorySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_InventorySubsystem : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Inventory - Unbind All Events"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregister_InventorySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_InventorySubsystem : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Inventory - Unbind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventRegister_InventorySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_InventorySubsystem : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Inventory - Bind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetAllItemsByGamerTag"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetAllItemsByGamerTag : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - TryGetAllItemsByGamerTag"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, TryGetAllItemsByGamerTag); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetAllCurrenciesByGamerTag"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetAllCurrenciesByGamerTag : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - TryGetAllCurrenciesByGamerTag"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, TryGetAllCurrenciesByGamerTag); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetAllItems"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetAllItems : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - TryGetAllItems"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, TryGetAllItems); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetAllCurrencies"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetAllCurrencies : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - TryGetAllCurrencies"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, TryGetAllCurrencies); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_BeginInventoryUpdate"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_BeginInventoryUpdate : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - BeginInventoryUpdate"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, BeginInventoryUpdate); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareAddCurrency"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareAddCurrency : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareAddCurrency"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareAddCurrency); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareRemoveCurrency"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareRemoveCurrency : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareRemoveCurrency"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareRemoveCurrency); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareModifyCurrency"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareModifyCurrency : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareModifyCurrency"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareModifyCurrency); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareCreateItem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareCreateItem : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareCreateItem"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareCreateItem); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareRemoveItem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareRemoveItem : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareRemoveItem"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareRemoveItem); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareRemoveItemWithId"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareRemoveItemWithId : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareRemoveItemWithId"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareRemoveItemWithId); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareModifyItem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareModifyItem : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareModifyItem"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareModifyItem); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_PrepareModifyItemById"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_PrepareModifyItemById : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - PrepareModifyItemById"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, PrepareModifyItemById); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetCurrencyAmountByGamerTag"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetCurrencyAmountByGamerTag : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - TryGetCurrencyAmountByGamerTag"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, TryGetCurrencyAmountByGamerTag); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetCurrencyAmount"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetCurrencyAmount : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Inventory - TryGetCurrencyAmount"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, TryGetCurrencyAmount); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CommitInventoryUpdate"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CommitInventoryUpdate : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Inventory - Operation - CommitInventoryUpdate"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, CommitInventoryUpdateOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_ModifyCurrencies"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_ModifyCurrencies : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Inventory - Operation - ModifyCurrencies"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, ModifyCurrenciesOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_FetchAllInventory"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchAllInventory : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Inventory - Operation - FetchAllInventory"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamInventorySubsystem, FetchAllInventoryOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamInventorySubsystem::StaticClass(); }

	virtual bool IsNodeSafeToIgnore() const override { return false; }
};

#undef LOCTEXT_NAMESPACE
