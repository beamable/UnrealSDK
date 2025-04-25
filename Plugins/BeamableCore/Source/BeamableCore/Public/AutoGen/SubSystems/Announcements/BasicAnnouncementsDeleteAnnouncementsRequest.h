
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/DeleteAnnouncementRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "BasicAnnouncementsDeleteAnnouncementsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAnnouncementsDeleteAnnouncementsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeleteAnnouncementRequestBody* Body = {};

	// Beam Base Request Declaration
	UBasicAnnouncementsDeleteAnnouncementsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make BasicAnnouncementsDeleteAnnouncements",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicAnnouncementsDeleteAnnouncementsRequest* Make(FString _Symbol, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsDeleteAnnouncementsSuccess, FBeamRequestContext, Context, UBasicAnnouncementsDeleteAnnouncementsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsDeleteAnnouncementsError, FBeamRequestContext, Context, UBasicAnnouncementsDeleteAnnouncementsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAnnouncementsDeleteAnnouncementsComplete, FBeamRequestContext, Context, UBasicAnnouncementsDeleteAnnouncementsRequest*, Request);

using FBasicAnnouncementsDeleteAnnouncementsFullResponse = FBeamFullResponse<UBasicAnnouncementsDeleteAnnouncementsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicAnnouncementsDeleteAnnouncementsFullResponse, FBasicAnnouncementsDeleteAnnouncementsFullResponse);
