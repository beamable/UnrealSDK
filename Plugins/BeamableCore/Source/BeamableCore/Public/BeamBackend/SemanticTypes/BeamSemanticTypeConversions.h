#pragma once

#include "CoreMinimal.h"
#include "BeamAccountId.h"
#include "BeamCid.h"
#include "BeamBackend/ReplacementTypes/BeamClientPermission.h"
#include "BeamGamerTag.h"
#include "BeamPid.h"
#include "BeamStatsType.h"
#include "BeamSemanticTypeConversions.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamSemanticTypeConversions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - CID To String", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_CidToString(FBeamCid Value) { return Value.AsString; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - CID To Int64", CompactNodeTitle = "->", BlueprintAutocast))
	static int64 Conv_CidToInt64(FBeamCid Value) { return Value.AsLong; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - CID To Text", CompactNodeTitle = "->", BlueprintAutocast))
	static FText Conv_CidToText(FBeamCid Value) { return FText::FromString(Value.AsString); }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - String To CID", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamCid Conv_StringToCid(FString Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Int64 To CID", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamCid Conv_Int64ToCid(int64 Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Text To CID", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamCid Conv_TextToCid(FText Value) { return Value.ToString(); }


	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - GamerTag To String", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_GamerTagToString(FBeamGamerTag Value) { return Value.AsString; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - GamerTag To Int64", CompactNodeTitle = "->", BlueprintAutocast))
	static int64 Conv_GamerTagToInt64(FBeamGamerTag Value) { return Value.AsLong; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - GamerTag To Text", CompactNodeTitle = "->", BlueprintAutocast))
	static FText Conv_GamerTagToText(FBeamGamerTag Value) { return FText::FromString(Value.AsString); }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - String To GamerTag", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamGamerTag Conv_StringToGamerTag(FString Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Int64 To GamerTag", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamGamerTag Conv_Int64ToGamerTag(int64 Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Text To GamerTag", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamGamerTag Conv_TextToGamerTag(FText Value) { return Value.ToString(); }


	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - AccountId To String", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_AccountIdToString(FBeamAccountId Value) { return Value.AsString; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - AccountId To Int64", CompactNodeTitle = "->", BlueprintAutocast))
	static int64 Conv_AccountIdToInt64(FBeamAccountId Value) { return Value.AsLong; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - AccountId To Text", CompactNodeTitle = "->", BlueprintAutocast))
	static FText Conv_AccountIdToText(FBeamAccountId Value) { return FText::FromString(Value.AsString); }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - String To AccountId", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamAccountId Conv_StringToAccountId(FString Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Int64 To AccountId", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamAccountId Conv_Int64ToAccountId(int64 Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Text To AccountId", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamAccountId Conv_TextToAccountId(FText Value) { return Value.ToString(); }


	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - PID To String", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_PidToString(FBeamPid Value) { return Value.AsString; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - PID To Text", CompactNodeTitle = "->", BlueprintAutocast))
	static FText Conv_PidToText(FBeamPid Value) { return FText::FromString(Value.AsString); }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - String To PID", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamPid Conv_StringToPid(FString Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Text To PID", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamPid Conv_TextToPid(FText Value) { return Value.ToString(); }


	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - StatsType To String", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_StatsTypeToString(FBeamStatsType Value) { return Value.AsString; }


	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - String To StatsType", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamStatsType Conv_StringToStatsType(FString Value) { return Value; }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - ClientPermission To Bool", CompactNodeTitle = "->", BlueprintAutocast))
	static bool Conv_ClientPermissionToBool(FBeamClientPermission Value) { return static_cast<bool>(Value); }

	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Bool To ClientPermission", CompactNodeTitle = "->", BlueprintAutocast))
	static FBeamClientPermission Conv_BoolToClientPermission(bool Value) { return Value; }
};
