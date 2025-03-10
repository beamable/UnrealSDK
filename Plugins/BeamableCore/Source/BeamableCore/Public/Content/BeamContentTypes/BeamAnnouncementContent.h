
#pragma once
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "Content/BeamContentObject.h"
#include "BeamAnnouncementContent.generated.h"

/**
 * Represents the content of an announcement in the Beamable system.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamAnnouncementContent : public UBeamContentObject
{
    GENERATED_BODY()

public:
    static inline const FString ContentId = TEXT("announcements");

 UFUNCTION()
 void GetContentType_UBeamAnnouncementContent(FString& Result);
 
    /**
     * The channel of the announcement, similar to an inbox category.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
    FString channel = TEXT("main");

    /**
     * The title of the announcement.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
    FString title = TEXT("title");

    /**
     * A brief summary of the announcement.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
    FString summary = TEXT("summary");

    /**
     * The main body content of the announcement.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
    FString body = TEXT("body");

    /**
     * The start date for the announcement's visibility (UTC).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
    FOptionalString start_date;

    /**
     * The end date for the announcement's visibility (UTC).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
    FOptionalString end_date;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beam")
    FOptionalMapOfString clientData;
};

DEFINE_CONTENT_TYPE_NAME(UBeamAnnouncementContent, "announcements")