
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EmptyResponse.h"

#include "DeleteMatchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMatchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteMatchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteMatchRequest* MakeDeleteMatchRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMatchSuccess, FBeamRequestContext, Context, UDeleteMatchRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMatchError, FBeamRequestContext, Context, UDeleteMatchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMatchComplete, FBeamRequestContext, Context, UDeleteMatchRequest*, Request);

using FDeleteMatchFullResponse = FBeamFullResponse<UDeleteMatchRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMatchFullResponse, FDeleteMatchFullResponse);
