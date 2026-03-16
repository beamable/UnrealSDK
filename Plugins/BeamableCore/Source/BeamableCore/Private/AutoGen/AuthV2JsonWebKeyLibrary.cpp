
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKeyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2JsonWebKeyLibrary::AuthV2JsonWebKeyToJsonString(const UAuthV2JsonWebKey* Serializable, const bool Pretty)
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

UAuthV2JsonWebKey* UAuthV2JsonWebKeyLibrary::Make(FOptionalString Alg, FOptionalString X5tS256, FOptionalString X5t, FOptionalString X, FOptionalString Use, FOptionalString Qi, FOptionalString Q, FOptionalString P, FOptionalString X5u, FOptionalString N, FOptionalString Kid, FOptionalString K, FOptionalString E, FOptionalString Dq, FOptionalString Dp, FOptionalString D, FOptionalString Crv, FOptionalString Kty, FOptionalString Y, FOptionalArrayOfString Oth, FOptionalArrayOfString KeyOps, FOptionalArrayOfString X5c, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2JsonWebKey>(Outer);
	Serializable->Alg = Alg;
	Serializable->X5tS256 = X5tS256;
	Serializable->X5t = X5t;
	Serializable->X = X;
	Serializable->Use = Use;
	Serializable->Qi = Qi;
	Serializable->Q = Q;
	Serializable->P = P;
	Serializable->X5u = X5u;
	Serializable->N = N;
	Serializable->Kid = Kid;
	Serializable->K = K;
	Serializable->E = E;
	Serializable->Dq = Dq;
	Serializable->Dp = Dp;
	Serializable->D = D;
	Serializable->Crv = Crv;
	Serializable->Kty = Kty;
	Serializable->Y = Y;
	Serializable->Oth = Oth;
	Serializable->KeyOps = KeyOps;
	Serializable->X5c = X5c;
	
	return Serializable;
}

void UAuthV2JsonWebKeyLibrary::Break(const UAuthV2JsonWebKey* Serializable, FOptionalString& Alg, FOptionalString& X5tS256, FOptionalString& X5t, FOptionalString& X, FOptionalString& Use, FOptionalString& Qi, FOptionalString& Q, FOptionalString& P, FOptionalString& X5u, FOptionalString& N, FOptionalString& Kid, FOptionalString& K, FOptionalString& E, FOptionalString& Dq, FOptionalString& Dp, FOptionalString& D, FOptionalString& Crv, FOptionalString& Kty, FOptionalString& Y, FOptionalArrayOfString& Oth, FOptionalArrayOfString& KeyOps, FOptionalArrayOfString& X5c)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Alg = Serializable->Alg;
		X5tS256 = Serializable->X5tS256;
		X5t = Serializable->X5t;
		X = Serializable->X;
		Use = Serializable->Use;
		Qi = Serializable->Qi;
		Q = Serializable->Q;
		P = Serializable->P;
		X5u = Serializable->X5u;
		N = Serializable->N;
		Kid = Serializable->Kid;
		K = Serializable->K;
		E = Serializable->E;
		Dq = Serializable->Dq;
		Dp = Serializable->Dp;
		D = Serializable->D;
		Crv = Serializable->Crv;
		Kty = Serializable->Kty;
		Y = Serializable->Y;
		Oth = Serializable->Oth;
		KeyOps = Serializable->KeyOps;
		X5c = Serializable->X5c;
	}
		
}

