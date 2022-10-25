
#include "AutoGen/FacebookPaymentUpdateResponseLibrary.h"

#include "CoreMinimal.h"


FString UFacebookPaymentUpdateResponseLibrary::FacebookPaymentUpdateResponseToJsonString(const UFacebookPaymentUpdateResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UFacebookPaymentUpdateResponse* UFacebookPaymentUpdateResponseLibrary::Make(FString Result, FString ContentType, UObject* Outer)
{
	auto Serializable = NewObject<UFacebookPaymentUpdateResponse>(Outer);
	Serializable->Result = Result;
	Serializable->ContentType = ContentType;
	
	return Serializable;
}

void UFacebookPaymentUpdateResponseLibrary::Break(const UFacebookPaymentUpdateResponse* Serializable, FString& Result, FString& ContentType)
{
	Result = Serializable->Result;
	ContentType = Serializable->ContentType;
		
}

