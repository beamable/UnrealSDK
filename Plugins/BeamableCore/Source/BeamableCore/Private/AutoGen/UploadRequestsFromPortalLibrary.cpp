
#include "BeamableCore/Public/AutoGen/UploadRequestsFromPortalLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUploadRequestsFromPortalLibrary::UploadRequestsFromPortalToJsonString(const UUploadRequestsFromPortal* Serializable, const bool Pretty)
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

UUploadRequestsFromPortal* UUploadRequestsFromPortalLibrary::Make(TArray<UUploadRequestFromPortal*> Request, FOptionalInt64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UUploadRequestsFromPortal>(Outer);
	Serializable->Request = Request;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UUploadRequestsFromPortalLibrary::Break(const UUploadRequestsFromPortal* Serializable, TArray<UUploadRequestFromPortal*>& Request, FOptionalInt64& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Request = Serializable->Request;
		PlayerId = Serializable->PlayerId;
	}
		
}

