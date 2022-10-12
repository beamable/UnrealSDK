
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AnnouncementRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "ObjectAnnouncementsDeleteAnnouncementsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectAnnouncementsDeleteAnnouncementsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAnnouncementRequestBody* Body;

	// Beam Base Request Declaration
	UObjectAnnouncementsDeleteAnnouncementsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Announcement,_Announcements,Outer"))
	static UObjectAnnouncementsDeleteAnnouncementsRequest* MakeObjectAnnouncementsDeleteAnnouncementsRequest(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsDeleteAnnouncementsSuccess, FBeamRequestContext, Context, UObjectAnnouncementsDeleteAnnouncementsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAnnouncementsDeleteAnnouncementsError, FBeamRequestContext, Context, UObjectAnnouncementsDeleteAnnouncementsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectAnnouncementsDeleteAnnouncementsComplete, FBeamRequestContext, Context, UObjectAnnouncementsDeleteAnnouncementsRequest*, Request);

using FObjectAnnouncementsDeleteAnnouncementsFullResponse = FBeamFullResponse<UObjectAnnouncementsDeleteAnnouncementsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectAnnouncementsDeleteAnnouncementsFullResponse, FObjectAnnouncementsDeleteAnnouncementsFullResponse);
