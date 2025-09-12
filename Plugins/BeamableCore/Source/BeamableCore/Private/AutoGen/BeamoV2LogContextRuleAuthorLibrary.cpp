
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRuleAuthorLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamoV2LogContextRuleAuthorLibrary::BeamoV2LogContextRuleAuthorToJsonString(const UBeamoV2LogContextRuleAuthor* Serializable, const bool Pretty)
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

UBeamoV2LogContextRuleAuthor* UBeamoV2LogContextRuleAuthorLibrary::Make(FString Email, FString AccountId, UObject* Outer)
{
	auto Serializable = NewObject<UBeamoV2LogContextRuleAuthor>(Outer);
	Serializable->Email = Email;
	Serializable->AccountId = AccountId;
	
	return Serializable;
}

void UBeamoV2LogContextRuleAuthorLibrary::Break(const UBeamoV2LogContextRuleAuthor* Serializable, FString& Email, FString& AccountId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Email = Serializable->Email;
		AccountId = Serializable->AccountId;
	}
		
}

