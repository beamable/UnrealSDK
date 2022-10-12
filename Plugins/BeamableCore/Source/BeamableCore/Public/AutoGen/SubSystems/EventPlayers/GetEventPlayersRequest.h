
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EventPlayerView.h"

#include "GetEventPlayersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetEventPlayersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetEventPlayersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetEventPlayersRequest* MakeGetEventPlayersRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetEventPlayersSuccess, FBeamRequestContext, Context, UGetEventPlayersRequest*, Request, UEventPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetEventPlayersError, FBeamRequestContext, Context, UGetEventPlayersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetEventPlayersComplete, FBeamRequestContext, Context, UGetEventPlayersRequest*, Request);

using FGetEventPlayersFullResponse = FBeamFullResponse<UGetEventPlayersRequest*, UEventPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnGetEventPlayersFullResponse, FGetEventPlayersFullResponse);