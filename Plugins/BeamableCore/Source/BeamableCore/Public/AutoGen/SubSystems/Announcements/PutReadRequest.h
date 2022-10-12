
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AnnouncementRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutReadRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutReadRequest : public UObject, public IBeamBaseRequestInterface
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
	UPutReadRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Announcement,_Announcements,Outer"))
	static UPutReadRequest* MakePutReadRequest(int64 _ObjectId, FOptionalString _Announcement, FOptionalArrayOfString _Announcements, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutReadSuccess, FBeamRequestContext, Context, UPutReadRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutReadError, FBeamRequestContext, Context, UPutReadRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutReadComplete, FBeamRequestContext, Context, UPutReadRequest*, Request);

using FPutReadFullResponse = FBeamFullResponse<UPutReadRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutReadFullResponse, FPutReadFullResponse);
