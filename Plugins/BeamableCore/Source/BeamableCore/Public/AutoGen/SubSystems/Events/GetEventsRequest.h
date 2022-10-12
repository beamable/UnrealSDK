
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EventObjectData.h"

#include "GetEventsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetEventsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetEventsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetEventsRequest* MakeGetEventsRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetEventsSuccess, FBeamRequestContext, Context, UGetEventsRequest*, Request, UEventObjectData*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetEventsError, FBeamRequestContext, Context, UGetEventsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetEventsComplete, FBeamRequestContext, Context, UGetEventsRequest*, Request);

using FGetEventsFullResponse = FBeamFullResponse<UGetEventsRequest*, UEventObjectData*>;
DECLARE_DELEGATE_OneParam(FOnGetEventsFullResponse, FGetEventsFullResponse);
