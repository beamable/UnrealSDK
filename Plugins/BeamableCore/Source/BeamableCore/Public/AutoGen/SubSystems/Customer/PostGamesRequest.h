
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/NewGameRequestBody.h"
#include "BeamableCore/Public/AutoGen/RealmView.h"

#include "PostGamesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGamesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UNewGameRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostGamesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PostGames",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostGamesRequest* Make(FString _CustomerId, FString _GameName, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGamesSuccess, FBeamRequestContext, Context, UPostGamesRequest*, Request, URealmView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGamesError, FBeamRequestContext, Context, UPostGamesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGamesComplete, FBeamRequestContext, Context, UPostGamesRequest*, Request);

using FPostGamesFullResponse = FBeamFullResponse<UPostGamesRequest*, URealmView*>;
DECLARE_DELEGATE_OneParam(FOnPostGamesFullResponse, FPostGamesFullResponse);
