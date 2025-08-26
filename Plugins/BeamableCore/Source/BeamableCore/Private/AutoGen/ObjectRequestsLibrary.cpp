
#include "BeamableCore/Public/AutoGen/ObjectRequestsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UObjectRequestsLibrary::ObjectRequestsToJsonString(const UObjectRequests* Serializable, const bool Pretty)
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

UObjectRequests* UObjectRequestsLibrary::Make(FOptionalInt64 PlayerId, FOptionalArrayOfObjectRequestBody Request, UObject* Outer)
{
	auto Serializable = NewObject<UObjectRequests>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Request = Request;
	
	return Serializable;
}

void UObjectRequestsLibrary::Break(const UObjectRequests* Serializable, FOptionalInt64& PlayerId, FOptionalArrayOfObjectRequestBody& Request)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Request = Serializable->Request;
	}
		
}

