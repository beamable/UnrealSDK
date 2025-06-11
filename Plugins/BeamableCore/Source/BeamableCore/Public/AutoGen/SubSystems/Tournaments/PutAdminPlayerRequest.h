
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/UpdatePlayerStatusRequestBody.h"
#include "BeamableCore/Public/AutoGen/AdminPlayerStatus.h"

#include "PutAdminPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAdminPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdatePlayerStatusRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutAdminPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make PutAdminPlayer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAdminPlayerRequest* Make(int64 _PlayerId, FString _TournamentId, UPlayerStatusUpdate* _Update, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminPlayerSuccess, FBeamRequestContext, Context, UPutAdminPlayerRequest*, Request, UAdminPlayerStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminPlayerError, FBeamRequestContext, Context, UPutAdminPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAdminPlayerComplete, FBeamRequestContext, Context, UPutAdminPlayerRequest*, Request);

using FPutAdminPlayerFullResponse = FBeamFullResponse<UPutAdminPlayerRequest*, UAdminPlayerStatus*>;
DECLARE_DELEGATE_OneParam(FOnPutAdminPlayerFullResponse, FPutAdminPlayerFullResponse);
