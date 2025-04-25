
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/AnnouncementQueryResponse.h"

#include "GetAnnouncementsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAnnouncementsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Include Deleted", Category="Beam")
	FOptionalBool bIncludeDeleted = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetAnnouncementsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make GetAnnouncements",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bIncludeDeleted,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAnnouncementsRequest* Make(int64 _ObjectId, FOptionalBool _bIncludeDeleted, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAnnouncementsSuccess, FBeamRequestContext, Context, UGetAnnouncementsRequest*, Request, UAnnouncementQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAnnouncementsError, FBeamRequestContext, Context, UGetAnnouncementsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAnnouncementsComplete, FBeamRequestContext, Context, UGetAnnouncementsRequest*, Request);

using FGetAnnouncementsFullResponse = FBeamFullResponse<UGetAnnouncementsRequest*, UAnnouncementQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAnnouncementsFullResponse, FGetAnnouncementsFullResponse);
