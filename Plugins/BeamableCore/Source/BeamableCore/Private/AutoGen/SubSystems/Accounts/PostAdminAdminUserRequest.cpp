
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostAdminAdminUserRequest.h"

void UPostAdminAdminUserRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("POST");
}

void UPostAdminAdminUserRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/admin/admin-user");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UPostAdminAdminUserRequest::BuildBody(FString& BodyString) const
{
	ensureAlways(Body);

	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Body->BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}

UPostAdminAdminUserRequest* UPostAdminAdminUserRequest::Make(FString _Email, FOptionalString _Role, FOptionalMapOfString _InitProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UPostAdminAdminUserRequest* Req = NewObject<UPostAdminAdminUserRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	Req->Body = NewObject<UCreateElevatedAccountRequestBody>(Req);
	Req->Body->Email = _Email;
	Req->Body->Role = _Role;
	Req->Body->InitProperties = _InitProperties;
	

	return Req;
}
