
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetSkusRequest.h"

void UGetSkusRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetSkusRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/commerce/skus");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Version.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("version"), *FString::FromInt(Version.Val));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetSkusRequest::BuildBody(FString& BodyString) const
{
	
}

UGetSkusRequest* UGetSkusRequest::Make(FOptionalInt64 _Version, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetSkusRequest* Req = NewObject<UGetSkusRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->Version = _Version;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
