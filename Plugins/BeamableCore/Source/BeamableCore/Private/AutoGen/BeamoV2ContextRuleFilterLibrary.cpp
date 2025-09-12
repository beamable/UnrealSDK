
#include "BeamableCore/Public/AutoGen/BeamoV2ContextRuleFilterLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2ContextRuleFilterLibrary::BeamoV2ContextRuleFilterToJsonString(const UBeamoV2ContextRuleFilter* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UBeamoV2ContextRuleFilter* UBeamoV2ContextRuleFilterLibrary::Make(FOptionalBeamoV2RuleOperationType PlayerIdOperationType, FOptionalBeamoV2RuleOperationType PathsOperationType, FOptionalArrayOfInt64 PlayerIds, FOptionalArrayOfString Paths, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2ContextRuleFilter>(Outer);
	Serializable->PlayerIdOperationType = PlayerIdOperationType;
	Serializable->PathsOperationType = PathsOperationType;
	Serializable->PlayerIds = PlayerIds;
	Serializable->Paths = Paths;
	
	return Serializable;
}

void UBeamoV2ContextRuleFilterLibrary::Break(const UBeamoV2ContextRuleFilter* Serializable, FOptionalBeamoV2RuleOperationType& PlayerIdOperationType, FOptionalBeamoV2RuleOperationType& PathsOperationType, FOptionalArrayOfInt64& PlayerIds, FOptionalArrayOfString& Paths)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerIdOperationType = Serializable->PlayerIdOperationType;
		PathsOperationType = Serializable->PathsOperationType;
		PlayerIds = Serializable->PlayerIds;
		Paths = Serializable->Paths;
	}
		
}

