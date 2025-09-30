
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CustomerActorUpdateGameHierarchyRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PutGamesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutGamesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game Id", Category="Beam")
	FString GameId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCustomerActorUpdateGameHierarchyRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutGamesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PutGames",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutGamesRequest* Make(FString _CustomerId, FString _GameId, TArray<URealmView*> _Realms, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutGamesSuccess, FBeamRequestContext, Context, UPutGamesRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutGamesError, FBeamRequestContext, Context, UPutGamesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutGamesComplete, FBeamRequestContext, Context, UPutGamesRequest*, Request);

using FPutGamesFullResponse = FBeamFullResponse<UPutGamesRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPutGamesFullResponse, FPutGamesFullResponse);
