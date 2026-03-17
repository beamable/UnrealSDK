
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsStatusGetSessionResponse.h"

#include "ApiSessionGetStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiSessionGetStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Ids", Category="Beam")
	FOptionalString PlayerIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Interval Secs", Category="Beam")
	FOptionalInt64 IntervalSecs = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiSessionGetStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", DisplayName="Make ApiSessionGetStatus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerIds,_IntervalSecs,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiSessionGetStatusRequest* Make(FOptionalString _PlayerIds, FOptionalInt64 _IntervalSecs, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiSessionGetStatusSuccess, FBeamRequestContext, Context, UApiSessionGetStatusRequest*, Request, UApiSessionsStatusGetSessionResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiSessionGetStatusError, FBeamRequestContext, Context, UApiSessionGetStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiSessionGetStatusComplete, FBeamRequestContext, Context, UApiSessionGetStatusRequest*, Request);

using FApiSessionGetStatusFullResponse = FBeamFullResponse<UApiSessionGetStatusRequest*, UApiSessionsStatusGetSessionResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiSessionGetStatusFullResponse, FApiSessionGetStatusFullResponse);
