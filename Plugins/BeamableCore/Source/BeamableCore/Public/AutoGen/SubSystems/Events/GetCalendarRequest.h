
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/EventsInDateRangeResponse.h"

#include "GetCalendarRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCalendarRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From")
	FOptionalString From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To")
	FOptionalString To;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query")
	FOptionalString Query;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;

	// Body Params
	

	// Beam Base Request Declaration
	UGetCalendarRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_From,_To,_Query,_Limit,Outer"))
	static UGetCalendarRequest* MakeGetCalendarRequest(FOptionalString _From, FOptionalString _To, FOptionalString _Query, FOptionalInt32 _Limit, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCalendarSuccess, FBeamRequestContext, Context, UGetCalendarRequest*, Request, UEventsInDateRangeResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCalendarError, FBeamRequestContext, Context, UGetCalendarRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCalendarComplete, FBeamRequestContext, Context, UGetCalendarRequest*, Request);

using FGetCalendarFullResponse = FBeamFullResponse<UGetCalendarRequest*, UEventsInDateRangeResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCalendarFullResponse, FGetCalendarFullResponse);
