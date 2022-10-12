
#include "GetAvailabilityRequest.h"

void UGetAvailabilityRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetAvailabilityRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/group-users/{objectId}/availability");
	Route = Route.Replace(TEXT("{objectId}"), *FString::FromInt(ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Name.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("name"), *Name.Val);
		bIsFirstQueryParam = false;
	}

	if(Tag.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("tag"), *Tag.Val);
		bIsFirstQueryParam = false;
	}

	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	bIsFirstQueryParam = false;
	
	if(bSubGroup.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), *TEXT("subGroup"), bSubGroup.Val ? *TEXT("true") : *TEXT("false"));
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetAvailabilityRequest::BuildBody(FString& BodyString) const
{
	
}

UGetAvailabilityRequest* UGetAvailabilityRequest::MakeGetAvailabilityRequest(int64 _ObjectId, FOptionalString _Name, FOptionalString _Tag, TMap<FString, FString> _Type, FOptionalBool _bSubGroup, UObject* Outer)
{
	UGetAvailabilityRequest* Req = NewObject<UGetAvailabilityRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	Req->Name = _Name;
	Req->Tag = _Tag;
	Req->Type = _Type;
	Req->bSubGroup = _bSubGroup;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
