
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAdminMeRequest.h"

void UGetAdminMeRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAdminMeRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/accounts/admin/me");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAdminMeRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAdminMeRequest* UGetAdminMeRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetAdminMeRequest* Req = NewObject<UGetAdminMeRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
