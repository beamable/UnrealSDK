
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRuleLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2LogContextRuleLibrary::BeamoV2LogContextRuleToJsonString(const UBeamoV2LogContextRule* Serializable, const bool Pretty)
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

UBeamoV2LogContextRule* UBeamoV2LogContextRuleLibrary::Make(bool bEnabled, FString Id, UBeamoV2LogContextRuleAuthor* Author, TArray<UBeamoV2ContextRuleFilter*> RuleFilters, FOptionalString Name, FOptionalString Description, FOptionalInt64 CreatedAt, FOptionalInt64 UpdatedAt, FOptionalInt64 ExpiresAt, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2LogContextRule>(Outer);
	Serializable->bEnabled = bEnabled;
	Serializable->Id = Id;
	Serializable->Author = Author;
	Serializable->RuleFilters = RuleFilters;
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->CreatedAt = CreatedAt;
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->ExpiresAt = ExpiresAt;
	
	return Serializable;
}

void UBeamoV2LogContextRuleLibrary::Break(const UBeamoV2LogContextRule* Serializable, bool& bEnabled, FString& Id, UBeamoV2LogContextRuleAuthor*& Author, TArray<UBeamoV2ContextRuleFilter*>& RuleFilters, FOptionalString& Name, FOptionalString& Description, FOptionalInt64& CreatedAt, FOptionalInt64& UpdatedAt, FOptionalInt64& ExpiresAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bEnabled = Serializable->bEnabled;
		Id = Serializable->Id;
		Author = Serializable->Author;
		RuleFilters = Serializable->RuleFilters;
		Name = Serializable->Name;
		Description = Serializable->Description;
		CreatedAt = Serializable->CreatedAt;
		UpdatedAt = Serializable->UpdatedAt;
		ExpiresAt = Serializable->ExpiresAt;
	}
		
}

