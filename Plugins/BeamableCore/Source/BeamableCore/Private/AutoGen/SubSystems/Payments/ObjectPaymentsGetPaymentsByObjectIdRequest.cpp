
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/ObjectPaymentsGetPaymentsByObjectIdRequest.h"

void UObjectPaymentsGetPaymentsByObjectIdRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UObjectPaymentsGetPaymentsByObjectIdRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/object/payments/{objectId}/");
	Route = Route.Replace(TEXT("{objectId}"), *FString::Printf(TEXT("%lld"), ObjectId));
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UObjectPaymentsGetPaymentsByObjectIdRequest::BuildBody(FString& BodyString) const
{
	
}

UObjectPaymentsGetPaymentsByObjectIdRequest* UObjectPaymentsGetPaymentsByObjectIdRequest::Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UObjectPaymentsGetPaymentsByObjectIdRequest* Req = NewObject<UObjectPaymentsGetPaymentsByObjectIdRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->ObjectId = _ObjectId;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
