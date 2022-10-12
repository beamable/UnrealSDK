
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/AnnouncementContentResponse.h"

#include "BasicAnnouncementsGetContentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAnnouncementsGetContentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicAnnouncementsGetContentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicAnnouncementsGetContentRequest* MakeBasicAnnouncementsGetContentRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsGetContentSuccess, FBeamRequestContext, Context, UBasicAnnouncementsGetContentRequest*, Request, UAnnouncementContentResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsGetContentError, FBeamRequestContext, Context, UBasicAnnouncementsGetContentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAnnouncementsGetContentComplete, FBeamRequestContext, Context, UBasicAnnouncementsGetContentRequest*, Request);

using FBasicAnnouncementsGetContentFullResponse = FBeamFullResponse<UBasicAnnouncementsGetContentRequest*, UAnnouncementContentResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicAnnouncementsGetContentFullResponse, FBasicAnnouncementsGetContentFullResponse);