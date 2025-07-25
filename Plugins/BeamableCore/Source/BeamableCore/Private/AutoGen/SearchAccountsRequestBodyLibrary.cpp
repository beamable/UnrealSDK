
#include "BeamableCore/Public/AutoGen/SearchAccountsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USearchAccountsRequestBodyLibrary::SearchAccountsRequestBodyToJsonString(const USearchAccountsRequestBody* Serializable, const bool Pretty)
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

USearchAccountsRequestBody* USearchAccountsRequestBodyLibrary::Make(FString Query, int32 Page, int32 Pagesize, UObject* Outer)
{
	auto Serializable = NewObject<USearchAccountsRequestBody>(Outer);
	Serializable->Query = Query;
	Serializable->Page = Page;
	Serializable->Pagesize = Pagesize;
	
	return Serializable;
}

void USearchAccountsRequestBodyLibrary::Break(const USearchAccountsRequestBody* Serializable, FString& Query, int32& Page, int32& Pagesize)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Query = Serializable->Query;
		Page = Serializable->Page;
		Pagesize = Serializable->Pagesize;
	}
		
}

