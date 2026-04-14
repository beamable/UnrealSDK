
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

UBeamoV2LogContextRule* UBeamoV2LogContextRuleLibrary::Make(bool bEnabled, EBeamBeamoV2LogLevel _LogLevel, TArray<UBeamoV2ContextRuleFilter*> RuleFilters, FOptionalString RuleId, FOptionalString Name, FOptionalString Description, FOptionalBeamoV2LogContextRuleAuthor Author, FOptionalBeamoV2LogContextRuleAuthor WhoLastEdit, FOptionalInt64 CreatedAt, FOptionalInt64 UpdatedAt, FOptionalInt64 ExpiresAt, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2LogContextRule>(Outer);
	Serializable->bEnabled = bEnabled;
	Serializable->LogLevel = _LogLevel;
	Serializable->RuleFilters = RuleFilters;
	Serializable->RuleId = RuleId;
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->Author = Author;
	Serializable->WhoLastEdit = WhoLastEdit;
	Serializable->CreatedAt = CreatedAt;
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->ExpiresAt = ExpiresAt;
	
	return Serializable;
}

void UBeamoV2LogContextRuleLibrary::Break(const UBeamoV2LogContextRule* Serializable, bool& bEnabled, EBeamBeamoV2LogLevel& _LogLevel, TArray<UBeamoV2ContextRuleFilter*>& RuleFilters, FOptionalString& RuleId, FOptionalString& Name, FOptionalString& Description, FOptionalBeamoV2LogContextRuleAuthor& Author, FOptionalBeamoV2LogContextRuleAuthor& WhoLastEdit, FOptionalInt64& CreatedAt, FOptionalInt64& UpdatedAt, FOptionalInt64& ExpiresAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bEnabled = Serializable->bEnabled;
		_LogLevel = Serializable->LogLevel;
		RuleFilters = Serializable->RuleFilters;
		RuleId = Serializable->RuleId;
		Name = Serializable->Name;
		Description = Serializable->Description;
		Author = Serializable->Author;
		WhoLastEdit = Serializable->WhoLastEdit;
		CreatedAt = Serializable->CreatedAt;
		UpdatedAt = Serializable->UpdatedAt;
		ExpiresAt = Serializable->ExpiresAt;
	}
		
}

