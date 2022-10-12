
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/DeleteAnnouncementRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "BasicAnnouncementsDeleteAnnouncementsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAnnouncementsDeleteAnnouncementsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UDeleteAnnouncementRequestBody* Body;

	// Beam Base Request Declaration
	UBasicAnnouncementsDeleteAnnouncementsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicAnnouncementsDeleteAnnouncementsRequest* MakeBasicAnnouncementsDeleteAnnouncementsRequest(FString _Symbol, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsDeleteAnnouncementsSuccess, FBeamRequestContext, Context, UBasicAnnouncementsDeleteAnnouncementsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsDeleteAnnouncementsError, FBeamRequestContext, Context, UBasicAnnouncementsDeleteAnnouncementsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAnnouncementsDeleteAnnouncementsComplete, FBeamRequestContext, Context, UBasicAnnouncementsDeleteAnnouncementsRequest*, Request);

using FBasicAnnouncementsDeleteAnnouncementsFullResponse = FBeamFullResponse<UBasicAnnouncementsDeleteAnnouncementsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicAnnouncementsDeleteAnnouncementsFullResponse, FBasicAnnouncementsDeleteAnnouncementsFullResponse);
