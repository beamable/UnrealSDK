#include "RawAPIs/Auth/BeamAuthApiModels.h"

#include "BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void FRegisterCustomerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
	Serializer->WriteValue(TEXT("password"), Password);
	Serializer->WriteValue(TEXT("projectName"), ProjectName);
	Serializer->WriteValue(TEXT("customerName"), CustomerName);
	Serializer->WriteValue(TEXT("alias"), Alias);
	UE_LOG(LogTemp, Display, TEXT("Serialized RegisterCustomer Request Body: EMAIL=%s, PASSWORD=%s, PROJECT=%s, CUSTOMER=%s, ALIAS=%s"), *Email, *Password, *ProjectName, *CustomerName, *Alias);
}

void FRegisterCustomerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Email = Bag->GetStringField(TEXT("email"));
	Password = Bag->GetStringField(TEXT("password"));
	ProjectName = Bag->GetStringField(TEXT("projectName"));
	CustomerName = Bag->GetStringField(TEXT("customerName"));
	Alias = Bag->GetStringField(TEXT("alias"));
}

void FRegisterCustomerResponseBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("cid"), CID);
	Serializer->WriteValue(TEXT("pid"), PID);

	Serializer->WriteObjectStart(TEXT("token"));
	TokenResponse.BeamSerializeProperties(Serializer);
	Serializer->WriteObjectEnd();

	UE_LOG(LogTemp, Display, TEXT("Serialized RegisterCustomer Response Body: CID=%llu, PID=%s, AccessToken=%s, TokenType=%s, RefreshToken=%s, ExpiresIn=%llu"), CID, *PID, *TokenResponse.AccessToken,
	       *TokenResponse.TokenType, *TokenResponse.RefreshToken, TokenResponse.ExpiresIn);
}

void FRegisterCustomerResponseBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("cid")), CID);
	PID = Bag->GetStringField(TEXT("pid"));

	TokenResponse = FTokenResponse{};
	TokenResponse.BeamDeserializeProperties(Bag->GetObjectField(TEXT("token")));
}


void FRegisterCustomerRequest::BuildRoute(FString& RouteString) const { RouteString.Appendf(TEXT("/basic/realms/customer")); }

void FRegisterCustomerRequest::BuildVerb(FString& VerbString) const { VerbString = TEXT("POST"); }

void FRegisterCustomerRequest::BuildBody(FString& BodyString) const
{
	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body.BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

void FMeResponseBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("email"), Email);	
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);	
	UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("deviceIds"), DeviceIds, Serializer);
}

void FMeResponseBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	Email = Bag->GetStringField(TEXT("email"));
	UBeamJsonUtils::DeserializeOptional<FString>(TEXT("language"), Bag, Language);	
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("scopes")), Scopes);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("thirdPartyAppAssociations")), ThirdPartyAppAssociations);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("deviceIds")), DeviceIds);
	
}

void FMeRequest::BuildVerb(FString& VerbString) const { VerbString = TEXT("GET"); }

void FMeRequest::BuildRoute(FString& RouteString) const { RouteString.Appendf(TEXT("/basic/accounts/me")); }

void FMeRequest::BuildBody(FString& BodyString) const { BodyString = TEXT(""); }

