
#include "BeamableUnreal\AutoGen/MSPlaygroundAddRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UMSPlaygroundAddRequestArgsLibrary::MSPlaygroundAddRequestArgsToJsonString(const UMSPlaygroundAddRequestArgs* Serializable, const bool Pretty)
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

UMSPlaygroundAddRequestArgs* UMSPlaygroundAddRequestArgsLibrary::Make(int32 A, int32 B, UObject* Outer)
{
	auto Serializable = NewObject<UMSPlaygroundAddRequestArgs>(Outer);
	Serializable->A = A;
	Serializable->B = B;
	
	return Serializable;
}

void UMSPlaygroundAddRequestArgsLibrary::Break(const UMSPlaygroundAddRequestArgs* Serializable, int32& A, int32& B)
{
	A = Serializable->A;
	B = Serializable->B;
		
}

