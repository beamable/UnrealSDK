
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/AnnouncementContentResponse.h"

#include "BasicAnnouncementsGetSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAnnouncementsGetSearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Date", Category="Beam")
	FOptionalString Date = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicAnnouncementsGetSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make BasicAnnouncementsGetSearch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Date,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicAnnouncementsGetSearchRequest* Make(FOptionalString _Date, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsGetSearchSuccess, FBeamRequestContext, Context, UBasicAnnouncementsGetSearchRequest*, Request, UAnnouncementContentResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAnnouncementsGetSearchError, FBeamRequestContext, Context, UBasicAnnouncementsGetSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAnnouncementsGetSearchComplete, FBeamRequestContext, Context, UBasicAnnouncementsGetSearchRequest*, Request);

using FBasicAnnouncementsGetSearchFullResponse = FBeamFullResponse<UBasicAnnouncementsGetSearchRequest*, UAnnouncementContentResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicAnnouncementsGetSearchFullResponse, FBasicAnnouncementsGetSearchFullResponse);
