
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UNewGameRequestBody* Body;

	// Beam Base Request Declaration
	UBasicRealmsPostGameRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", DisplayName="Beam - Make BasicRealmsPostGame",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicRealmsPostGameRequest* Make(FString _GameName, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsPostGameSuccess, FBeamRequestContext, Context, UBasicRealmsPostGameRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsPostGameError, FBeamRequestContext, Context, UBasicRealmsPostGameRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicRealmsPostGameComplete, FBeamRequestContext, Context, UBasicRealmsPostGameRequest*, Request);

using FBasicRealmsPostGameFullResponse = FBeamFullResponse<UBasicRealmsPostGameRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicRealmsPostGameFullResponse, FBasicRealmsPostGameFullResponse);
