
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/NewGameRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "BasicRealmsPostGameRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicRealmsPostGameRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UNewGameRequestBody* Body;

	// Beam Base Request Declaration
	UBasicRealmsPostGameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicRealmsPostGameRequest* MakeBasicRealmsPostGameRequest(FString _GameName, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsPostGameSuccess, FBeamRequestContext, Context, UBasicRealmsPostGameRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsPostGameError, FBeamRequestContext, Context, UBasicRealmsPostGameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicRealmsPostGameComplete, FBeamRequestContext, Context, UBasicRealmsPostGameRequest*, Request);

using FBasicRealmsPostGameFullResponse = FBeamFullResponse<UBasicRealmsPostGameRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicRealmsPostGameFullResponse, FBasicRealmsPostGameFullResponse);
