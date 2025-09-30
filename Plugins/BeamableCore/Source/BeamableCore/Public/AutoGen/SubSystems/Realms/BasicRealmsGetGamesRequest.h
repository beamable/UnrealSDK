
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetGameResponse.h"

#include "BasicRealmsGetGamesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicRealmsGetGamesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicRealmsGetGamesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make BasicRealmsGetGames",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicRealmsGetGamesRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetGamesSuccess, FBeamRequestContext, Context, UBasicRealmsGetGamesRequest*, Request, UGetGameResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetGamesError, FBeamRequestContext, Context, UBasicRealmsGetGamesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicRealmsGetGamesComplete, FBeamRequestContext, Context, UBasicRealmsGetGamesRequest*, Request);

using FBasicRealmsGetGamesFullResponse = FBeamFullResponse<UBasicRealmsGetGamesRequest*, UGetGameResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicRealmsGetGamesFullResponse, FBasicRealmsGetGamesFullResponse);
