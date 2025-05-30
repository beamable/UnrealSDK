
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AddRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UAddRequestArgsLibrary::AddRequestArgsToJsonString(const UAddRequestArgs* Serializable, const bool Pretty)
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

UAddRequestArgs* UAddRequestArgsLibrary::Make(int32 A, int32 B, UObject* Outer)
{
	auto Serializable = NewObject<UAddRequestArgs>(Outer);
	Serializable->A = A;
	Serializable->B = B;
	
	return Serializable;
}

void UAddRequestArgsLibrary::Break(const UAddRequestArgs* Serializable, int32& A, int32& B)
{
	A = Serializable->A;
	B = Serializable->B;
		
}

